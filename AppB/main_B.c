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
#include <cmsis_gcc.h>

void serial_transmit(char *c);
void serial_read(char *buf, int len);


volatile char __attribute__((section(".header"))) image_header[0x400];

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    //This is needed on XMEGA examples, but not normally on ARM. ARM doesn't have this macro normally anyway.
    #ifdef __AVR__
    _delay_ms(20);
    #endif

    serial_transmit("Starting application B...\n"); 
    app_loop_b();

}


volatile void app_loop_b()
{
    volatile uint8_t led_ok_state = 0;
    volatile uint8_t led_error_state = 0;

    volatile uint8_t counter = 0;

    char str[64];

    while(1)
    {
        serial_transmit("This is not in App A! \n");
        led_ok_state = 0;
        led_error_state = 1;

        led_ok(led_ok_state);
        led_error(led_error_state);       

        counter++;

        const uint16_t repeat_transmit = 10;
        volatile uint16_t i = 0;
        for(i = 0; i < repeat_transmit; i++)
        {
            sprintf(str, "Running B, switching led_ok: %x, led_err: %x Counter : %x \n", led_ok_state, led_error_state, counter);
            serial_transmit(str);
        }

        led_ok_state = 1;
        led_error_state = 0;

        led_ok(led_ok_state);
        led_error(led_error_state);      

        for(i = 0; i < repeat_transmit; i++)
        {
            sprintf(str, "Running B, switching led_ok: %x, led_err: %x Counter : %x \n", led_ok_state, led_error_state, counter);
            serial_transmit(str);
        }              
    }
}

void serial_transmit(char *c)
{
    do
    {
        putch(*c);
    }while (*++c);
}


void serial_read(char *buf, int len)
{
    for(int i = 0; i < len; i++) {
        while (buf[i] = getch(), buf[i] == '\0');

        if (buf[i] == '\n') {
            buf[i] = '\0';
            return;
        }
    }
    buf[len - 1] = '\0';
}



