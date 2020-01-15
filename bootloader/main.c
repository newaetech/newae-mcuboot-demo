/*
    This file is part of the NewAE Chip Armour demo
    
    Copyright (C) 2012-2015 NewAE Technology Inc.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdint.h>
#include <hal.h>
#include <stm32f303xc.h> //TODO: this is a hack to get the code to compile, find the correct way to get stm32f3xx.h included
#include <core_cm4.h>
#include "flash_layout.h"
#include "flash_map/flash_map.h"
#include "Driver_Flash.h"
#include "bootutil/bootutil.h"
#include "bootutil/image.h"
#include "serial_abstract.h"
#include "Driver_Common.h"
#include <cmsis_gcc.h>
#include "security_cnt.h"

struct arm_vector_table {
    uint32_t msp;
    uint32_t reset;
};

/**
 * Prototypes
 * */
static void do_boot(struct boot_rsp *rsp);
volatile void jump_to_application();

//TODO AR: remove debug proto
static uint32_t
flash_read_word(uint32_t address);

/* Flash device name must be specified by target */
extern ARM_DRIVER_FLASH FLASH_DEV_NAME;

int main(void)
{

    platform_init();
    init_uart();
    trigger_setup();

    //TODO AR: remove test code (this is useful for testing flash operations)

/*
    FLASH_DEV_NAME.EraseSector(FLASH_AREA_0_OFFSET);

    volatile uint8_t data[] = {1u, 0x56u, 3u,
                              1u, 0x89u, 3u,
                              1u, 0x98, 3u,
                              1u, 0x78, 3u,
                              1u, 0x65, 3u, 0x7};

    FLASH_DEV_NAME.ProgramData(FLASH_AREA_0_OFFSET, &data, sizeof(data));

    serial_transmit("Reading App A (Untouched)\n");
    serial_memory_dump(FLASH_AREA_0_OFFSET, 100);

    serial_transmit("Reading App B (Untouched)\n");
    serial_memory_dump(FLASH_AREA_2_OFFSET, 100);

    while(1){;}    
*/

    //This is needed on XMEGA examples, but not normally on ARM. ARM doesn't have this macro normally anyway.
    #ifdef __AVR__
    _delay_ms(20);
    #endif 

    //while(1){;}

    /* Start of bl2_main calls */

    serial_transmit("Starting bootloader...\n"); 

    struct boot_rsp rsp;
    int rc;

    rc = boot_nv_security_counter_init();
    if (rc != 0) {
        while (1)
        {
            serial_transmit("Error while initializing the security counter");
        }
    }

    rc = boot_go(&rsp);
    serial_transmit("End of boot go \n");
    if (rc != 0) {
        serial_transmit("No bootable image found!\n");   
        while (1)
        {
        }
    }

    jump_to_application(); //TODO AR: is this best here?

    flash_area_warn_on_open();
    serial_transmit("Jumping to the first image slot-- Address at app start");

    do_boot(&rsp);

    while(1)
    {
        serial_transmit("Never should have got here!\n");  
    } 

    return 1;
}

/**
 * Copied over from bl2_main.c
 */
static void do_boot(struct boot_rsp *rsp)
{
    /* Clang at O0, stores variables on the stack with SP relative addressing.
     * When manually set the SP then the place of reset vector is lost.
     * Static variables are stored in 'data' or 'bss' section, change of SP has
     * no effect on them.
     */
    static struct arm_vector_table *vt;
    uintptr_t flash_base;
    int rc;

    /* The beginning of the image is the ARM vector table, containing
     * the initial stack pointer address and the reset vector
     * consecutively. Manually set the stack pointer and jump into the
     * reset vector
     */
    rc = flash_device_base(rsp->br_flash_dev_id, &flash_base);

    if (rsp->br_hdr->ih_flags & IMAGE_F_RAM_LOAD) {
       /* The image has been copied to SRAM, find the vector table
        * at the load address instead of image's address in flash
        */
        vt = (struct arm_vector_table *)(rsp->br_hdr->ih_load_addr +
                                         rsp->br_hdr->ih_hdr_size);
    } else {
        /* Using the flash address as not executing in SRAM */
        vt = (struct arm_vector_table *)(flash_base +
                                         rsp->br_image_off +
                                         rsp->br_hdr->ih_hdr_size);
    }

    rc = FLASH_DEV_NAME.Uninitialize();
    if(rc != ARM_DRIVER_OK) {
        serial_transmit("Error while uninitializing Flash Interface");
    }

#if BOOT_LOG_LEVEL > BOOT_LOG_LEVEL_OFF
    stdio_uninit();
#endif

#if defined(__ARM_ARCH_8M_MAIN__) || defined(__ARM_ARCH_8M_BASE__)
    /* Restore the Main Stack Pointer Limit register's reset value
     * before passing execution to runtime firmware to make the
     * bootloader transparent to it.
     */
    __set_MSPLIM(0);
#endif

    jump_to_application();
}

volatile void jump_to_application()
{    
    extern void *_app_start[];

    asm("cpsid i");
    asm("ldr sp, = _estack");
    ((void(*)())_app_start[1])();

}
/*!
 * 
 * \brief Chain-loading the next image in the boot sequence.
 * Copied over from bl2_main.c
 * Removed: __attribute__((naked)) from function signature 
 * __ASM -> __asm (ASM seemed to be for IAR compiler)
 * 
 * This function calls the Reset_Handler of the next image in the boot sequence,
 * usually it is the secure firmware. Before passing the execution to next image
 * there is conditional rule to remove the secrets from the memory. This must be
 * done if the following conditions are satisfied:
 *  - Memory is shared between SW components at different stages of the trusted
 *    boot process.
 *  - There are secrets in the memory: KDF parameter, symmetric key,
 *    manufacturer sensitive code/data, etc.
 */
__attribute__((naked)) void boot_jump_to_next_image(uint32_t reset_handler_addr)
{
    __asm volatile(
        ".syntax unified                 \n"
        "mov     r7, r0                  \n"
        "bl      boot_clear_bl2_ram_area \n" /* Clear RAM before jump */
        "movs    r0, #0                  \n" /* Clear registers: R0-R12, */
        "mov     r1, r0                  \n" /* except R7 */
        "mov     r2, r0                  \n"
        "mov     r3, r0                  \n"
        "mov     r4, r0                  \n"
        "mov     r5, r0                  \n"
        "mov     r6, r0                  \n"
        "mov     r8, r0                  \n"
        "mov     r9, r0                  \n"
        "mov     r10, r0                 \n"
        "mov     r11, r0                 \n"
        "mov     r12, r0                 \n"
        "mov     lr,  r0                 \n"
        "bx      r7                      \n" /* Jump to Reset_handler */
    );
}

__attribute__((naked)) void boot_clear_bl2_ram_area(void)
{
    __asm volatile(
        ".syntax unified                             \n"
        "movs    r0, #0                              \n"
        //"ldr     r1, =Image$$ER_DATA$$Base           \n"
        //"ldr     r2, =Image$$ARM_LIB_HEAP$$ZI$$Limit \n"
        "subs    r2, r2, r1                          \n"
        "Loop:                                       \n"
        "subs    r2, #4                              \n"
        "blt     Clear_done                          \n"
        "str     r0, [r1, r2]                        \n"
        "b       Loop                                \n"
        "Clear_done:                                 \n"
        "bx      lr                                  \n"
         : : : "r0" , "r1" , "r2" , "memory"
    );
}


void serial_memory_dump(uint32_t start_addr, uint32_t count)
{
    uint32_t sizeOfUint32 = sizeof(uint32_t);
    char str[64];

    for(volatile uint32_t address = start_addr; address < (start_addr+count); address+=4)
    {
        volatile uint32_t word = flash_read_word(address);
        sprintf(str, "%x, %x", address, word);
        serial_transmit(str);
        sprintf(str, "\n");
        serial_transmit(str);
    }
}

