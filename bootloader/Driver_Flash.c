/*
 * Copyright (c) 2013-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file is a derivative of a previous version of
 * platform/ext/target/musca_b1/CMSIS_Driver/Driver_Flash.c
 * Git SHA: 9f3da0b83e45e6d26ad0be45c090d2e4382fb04f
 */

/* FIXME: This interim flash driver uses BRAM to emulate flash for SST.
 * Code is still running on QSPI, and only direct read is supported,
 * write is not supported yet.
 * It should be replaced with a real flash driver.
 */

#include <string.h>
#include <stdint.h>
#include "RTE_Device.h"
#include "Driver_Flash.h"
#include "flash_layout.h"
#include "stm32f3xx_hal_def.h"
#include "stm32f3xx_hal_flash_ex.h"
#include "stm32f3xx_hal_flash.h"
#include "serial_abstract.h"
#include "bootutil_priv.h"

typedef unsigned long uint32_t;
typedef long int32_t;

#define BL_PAGE_COUNT           (FLASH_AREA_BL2_SIZE / FLASH_AREA_PAGE_SIZE) 
#define APP_SPACE_PAGE_COUNT    (FLASH_AREA_0_SIZE / FLASH_AREA_PAGE_SIZE) 

typedef struct
{
    uint32_t page[FLASH_AREA_PAGE_SIZE];
}ts_flash_page_layout;

typedef struct FL_STM32F303
{
    
}ts_flash_layout;

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  ((void)arg)
#endif

/* Driver version */
#define ARM_FLASH_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1, 0)

/*
#define FLASH_REDIRECT_BASE   SST_FLASH_AREA_ADDR
#define FLASH_REDIRECT_LIMIT  (FLASH_REDIRECT_BASE   \
                               + FLASH_SST_AREA_SIZE \
                               + FLASH_ITS_AREA_SIZE \
                               + FLASH_NV_COUNTERS_AREA_SIZE)
#define FLASH_REDIRECT_DEST   0x20000400//NOTE AR: From where this is used is supposed to be volatile memory (BRAM). Using SRAM at the end
                                       //which should workout to 12K + 0x20000000 = 0x20000400
*/

#define FLASH0_BASE_S         0x08006000 //Start at writable space, not at bootloader
#define FLASH0_BASE_NS        0x00180000 //TODO: Not used
#define FLASH0_SIZE           0x40000
#define FLASH0_SECTOR_SIZE    0x0000800 //2 kB 
#define FLASH0_PAGE_SIZE      0x0000800 //2 kB 
#define FLASH0_PROGRAM_UNIT   0x1        // Minimum write size 

#define FLASH_REDIRECT_BASE FLASH0_BASE_S
#define FLASH_REDIRECT_LIMIT FLASH_REGION_1_MAX

static inline void flash_unlock(void);
static inline void flash_lock(void);
static int8_t MemMap_Flash_WriteWord(uint32_t address, uint32_t word);

/*
 * ARM FLASH device structure
 */
struct arm_flash_dev_t {
    const uint32_t memory_base;   /*!< FLASH memory base address */
    ARM_FLASH_INFO *data;         /*!< FLASH data */
};

/* Flash Status */
static ARM_FLASH_STATUS FlashStatus = {0, 0, 0};

/* Driver Version */
static const ARM_DRIVER_VERSION DriverVersion = {
    ARM_FLASH_API_VERSION,
    ARM_FLASH_DRV_VERSION
};

/* Driver Capabilities */
static const ARM_FLASH_CAPABILITIES DriverCapabilities = {
    0, /* event_ready */
    2, /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
    1  /* erase_chip */
};

/*Prototypes*/
static int32_t ARM_Flash_EraseSector(uint32_t addr);

static int32_t is_range_valid(struct arm_flash_dev_t *flash_dev,
                              uint32_t offset)
{

    uint32_t flash_limit = 0;
    volatile int32_t rc = 0;

    if (offset >= FLASH0_BASE_S && offset <= FLASH_REGION_1_MAX) 
    {
        rc = 0;
    }
    else
    {
        boot_transmit_error_code_serial(100,offset);  
        rc = -1;
    }


    return rc;
}

static int32_t is_write_aligned(struct arm_flash_dev_t *flash_dev,
                                uint32_t param)
{
    int32_t rc = 0;

    if ((param % flash_dev->data->program_unit) != 0) {
        rc = -1;
    }
    return rc;
}

static int32_t is_sector_aligned(struct arm_flash_dev_t *flash_dev,
                                 uint32_t offset)
{

    int32_t rc = 0;

    if ((offset % flash_dev->data->sector_size) != 0) {
        rc = -1;
    }
    return rc;
}

#if (RTE_FLASH0)
static ARM_FLASH_INFO ARM_FLASH0_DEV_DATA = {
    .sector_info  = NULL,                  /* Uniform sector layout */
    .sector_count = FLASH0_SIZE / FLASH0_SECTOR_SIZE,
    .sector_size  = FLASH0_SECTOR_SIZE,
    .page_size    = FLASH0_PAGE_SIZE,
    .program_unit = FLASH0_PROGRAM_UNIT,
    .erased_value = 0xFF};

static struct arm_flash_dev_t ARM_FLASH0_DEV = {
#if (__DOMAIN_NS == 1)
    .memory_base = FLASH0_BASE_NS,
#else
    .memory_base = FLASH0_BASE_S,
#endif /* __DOMAIN_NS == 1 */
    .data        = &(ARM_FLASH0_DEV_DATA)};

struct arm_flash_dev_t *FLASH0_DEV = &ARM_FLASH0_DEV;

/*
 * Functions
 */

static ARM_DRIVER_VERSION ARM_Flash_GetVersion(void)
{
    return DriverVersion;
}

static ARM_FLASH_CAPABILITIES ARM_Flash_GetCapabilities(void)
{
    return DriverCapabilities;
}

static int32_t ARM_Flash_Initialize(ARM_Flash_SignalEvent_t cb_event)
{
    //ARG_UNUSED(cb_event);
    //HAL_FLASH_Unlock();
    return ARM_DRIVER_OK;
}

static int32_t ARM_Flash_Uninitialize(void)
{
    /* Nothing to be done */
    HAL_FLASH_Lock();
    return ARM_DRIVER_OK;
}

static int32_t ARM_Flash_PowerControl(ARM_POWER_STATE state)
{
    switch (state) {
    case ARM_POWER_FULL:
        /* Nothing to be done */
        return ARM_DRIVER_OK;
        break;

    case ARM_POWER_OFF:
    case ARM_POWER_LOW:
    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

volatile uint32_t debug_read_addr = 0;
volatile uint32_t debug_read_cnt = 0;
volatile uint32_t debug_read_rc = 0;
static int32_t ARM_Flash_ReadData(uint32_t addr, void *data, uint32_t cnt)
{
    debug_read_addr = addr;
    debug_read_cnt = cnt;

    //uint32_t start_addr = FLASH0_DEV->memory_base + addr;
    uint32_t start_addr = addr;

    int32_t rc = 0;

    char test[64];
    sprintf(test, "Read at address: %x Cnt: %x \n", addr, cnt);
    serial_transmit(test);

    /* Check flash memory boundaries */
    rc = is_range_valid(FLASH0_DEV, addr + cnt);
    debug_read_rc = rc;
    if (rc != 0) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }
		
    memcpy(data, (void*)start_addr, cnt);
    
    return ARM_DRIVER_OK;
}

static volatile int32_t ARM_Flash_ProgramData(uint32_t addr, const void *data,
                                     uint32_t cnt)
{
    char test[64];
    sprintf(test, "Programmed address: %x Cnt: %x", addr, cnt);
    serial_transmit(test);

    volatile uint32_t mem_base = FLASH0_DEV->memory_base;
    int32_t rc = 0;

    /* Check flash memory boundaries and alignment with minimal write size */
    rc  = is_range_valid(FLASH0_DEV, addr + cnt);
    rc |= is_write_aligned(FLASH0_DEV, addr);
    rc |= is_write_aligned(FLASH0_DEV, cnt);

    if (rc != 0) {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    flash_unlock();

    uint32_t end_address = addr + cnt;

    uint32_t size_of_base_unit = sizeof(uint32_t);
    uint32_t* elem_ptr = (uint32_t*)data;

    static uint32_t write_count = 0;

    for(volatile uint32_t elem_cnt = 0; elem_cnt < cnt/4; elem_cnt++)
    {
        volatile uint32_t word = *(elem_ptr + elem_cnt);
        volatile uint32_t address = (uint32_t)(addr + (elem_cnt * size_of_base_unit));

        if(HAL_FLASH_Write_Word(address, word) == HAL_ERROR)
        {
            return ARM_DRIVER_ERROR_TIMEOUT;
        };
        write_count++;
    }

    char str[64];
    sprintf(str, "Write count: %u", write_count);    

    flash_lock();
 
    return ARM_DRIVER_OK;
}


#define FLASH_UNLOCK_KEY1	0x45670123
#define	FLASH_UNLOCK_KEY2	0xCDEF89AB

static inline void flash_unlock(void)
{
	if(FLASH->CR & FLASH_CR_LOCK)
	{
		FLASH->KEYR = FLASH_UNLOCK_KEY1;
		FLASH->KEYR = FLASH_UNLOCK_KEY2;
        /* Authorizes the Option Byte register programming */
        FLASH->OPTKEYR = FLASH_OPTKEY1;
        FLASH->OPTKEYR = FLASH_OPTKEY2;
	}
}

static inline void flash_lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}


static int32_t ARM_Flash_EraseSector(uint32_t addr)
{
    uint32_t rc = 0;
    char str[64];

    rc  = is_range_valid(FLASH0_DEV, addr);
    rc |= is_sector_aligned(FLASH0_DEV, addr);
    if (rc != 0) {
        sprintf(str, "Failed to erase page at: Addr: %x \n", addr);
        serial_transmit(str);
        return ARM_DRIVER_ERROR_PARAMETER;
    }

    flash_unlock();
    FLASH_PageErase(addr);
    flash_lock();

    sprintf(str, "Just erased page at: Addr: %x \n", addr);
    serial_transmit(str);
    
    return ARM_DRIVER_OK;
}

volatile uint32_t debug_index = 0;

//AR: Unused
static int32_t ARM_Flash_EraseChip(void)
{

    return 0;
#if 0
    uint32_t i;
    uint32_t addr = FLASH0_DEV->memory_base;
    int32_t rc = ARM_DRIVER_ERROR_UNSUPPORTED;

    /* Check driver capability erase_chip bit */
    if (DriverCapabilities.erase_chip == 1) {
        for (i = 0; i < FLASH0_DEV->data->sector_count; i++) {
            /* Redirecting SST storage to BRAM */
            if (addr >= FLASH_REDIRECT_BASE && addr <= FLASH_REDIRECT_LIMIT) {
                memset((void *)(FLASH_REDIRECT_DEST +
                        (addr - FLASH0_DEV->memory_base - FLASH_REDIRECT_BASE)),
                        FLASH0_DEV->data->erased_value,
                        FLASH0_DEV->data->sector_size);
            }
            /* else {
             *     Flash driver for QSPI is not ready, fall through.
             * }
             */

            addr += FLASH0_DEV->data->sector_size;
            rc = ARM_DRIVER_OK;
        }
    }
    return rc;
#endif
}

static ARM_FLASH_STATUS ARM_Flash_GetStatus(void)
{
    return FlashStatus;
}

static ARM_FLASH_INFO *ARM_Flash_GetInfo(void)
{
    return FLASH0_DEV->data;
}

ARM_DRIVER_FLASH Driver_FLASH0 = {
    ARM_Flash_GetVersion,
    ARM_Flash_GetCapabilities,
    ARM_Flash_Initialize,
    ARM_Flash_Uninitialize,
    ARM_Flash_PowerControl,
    ARM_Flash_ReadData,
    ARM_Flash_ProgramData,
    ARM_Flash_EraseSector,
    ARM_Flash_EraseChip,
    ARM_Flash_GetStatus,
    ARM_Flash_GetInfo
};
#endif /* RTE_FLASH0 */
