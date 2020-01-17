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
#include <stm32f303xc.h> 
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

/**
 * Prototypes
 * */
volatile void jump_to_application();

int main(void)
{

    platform_init();
    init_uart();
    //trigger_setup();



    //This is needed on XMEGA examples, but not normally on ARM. ARM doesn't have this macro normally anyway.
    #ifdef __AVR__
    _delay_ms(20);
    #endif 

    /* Start of bl2_main calls */
    serial_transmit("Starting bootloader process...\n"); 

    struct boot_rsp rsp;
    int rc;

    rc = boot_nv_security_counter_init();
    if (rc != 0) {
        serial_transmit("!!Error while initializing the security counter\n");
        while(1){;}
    }

    rc = boot_go(&rsp);
    serial_transmit("End of boot go \n");
    if (rc != 0) {
        serial_transmit("!!No bootable image found!\n");   
        while(1){;}
    }

    jump_to_application();

    serial_transmit("!!Never should have got here!\n");
    while(1){;}

    return 1;
}

volatile void jump_to_application()
{    
    extern void *_app_start[];

    asm("cpsid i");
    asm("ldr sp, = _estack");
    ((void(*)())_app_start[1])();
}


