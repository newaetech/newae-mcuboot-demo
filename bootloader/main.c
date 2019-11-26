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
#include "hal.h"
#include "bootutil/bootutil.h"
#include "serial_abstract.h"

int main(void)
{

    platform_init();
    init_uart();
    trigger_setup();

    //This is needed on XMEGA examples, but not normally on ARM. ARM doesn't have this macro normally anyway.
    #ifdef __AVR__
    _delay_ms(20);
    #endif


    /* Start of bl2_main calls */

    serial_transmit("Starting bootloader...\n");    

    struct boot_rsp rsp;
    int rc;

    rc = boot_go(&rsp);
    if (rc != 0) {
        serial_transmit("No bootable image found!\n");   
        while (1){;}
    }

    serial_transmit("Never should have got here!\n");   

    return 1;
}
