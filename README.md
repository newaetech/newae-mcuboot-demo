# NewAE Secure Bootloader
This project was ported over from Trusted Firmware-M and adapted to run on the STM32F303RCT7

It can only support 2 slots (Application Running/Application to Run)

RSA 2048 is validated to be working (A single bit change will prevent application from running)

## Getting Started
This project is only validated for use on the STM32F303RCT7. Due to the limited memory the max App size that can be programmed is limited
to 64k

This project is based off of three main sources
-Trusted Firmware-M (tf-m) for base loader.c and support modules [tfm](https://git.trustedfirmware.org/trusted-firmware-m.git)
-ChipWhisperer for base hardware platform and python programming [cw](https://github.com/newaetech/chipwhisperer)
-Juul image signing tool as tf-m had features the STM32F303 could not support (Secure/Non-Secure partitions) [mcuboot](https://github.com/JuulLabs-OSS/mcuboot)

In future developments NewAE's Chip Armour will be used

# Operation

The bootloader sits at the base flash address. In the demo App A will be programming where the bootloader will jump too. App B is the app that
will be swapped over to the starting jump address (Marked by the --pad parameter with the signing tool). It will verify the signature generated with 
the .pem file and if valid, swap B over and start it.

## GIT Source
Note all development occurs on here [trunk](https://github.com/newaetech/ca_bootloader) and [branch](https://github.com/newaetech/chipwhisperer/tree/CW_CA_BL)

## Running
To make and run the demo simply run

##  Windows:
..\ca_bootloader\Scripts\demo_build_bootloader_and_apps.bat

## Linux
..\ca_bootloader\Scripts\demo_build_bootloader_and_apps.sh


# Development Notes

Each application has only 64KB space allocated for it.
The app to be loaded must use the same starting ROM addresses. The offset in programming is handled with firmware_loader.py 

If you wish to modify the bootloader it must not exceed address space 0x08008000 after programming. Heavy optimization is recommended

The primary base of the firmware is handled in the chipwhisperer libraries. If you want to port to a different micro flash_layout.h and Driver_Flash.c are the primary
starting points.

##  Python Scripts

FirmwareLoader\firmware_loader.py can be used to automatically program the applications at the correct offsets. Default paths will be used unless specified otherwise.

##  Linker Script Notes

Note: The addresses in the example are only gaurenteed to work for the STM32F303RCT7

Bootloader: Starting address 0x08000000
App A: Starting address 0x08008000
App B: Starting address 0x08008000 ***NOTE*** When programming it, it must be offset by 0x10000 (see firmware_loader.py)

## Header Allocation

For the signing tool to work header space must be allocated in your application.

Example in linkerscript:
  .header :
  {
    . = ALIGN(4);
    KEEP(*(.header))
    . = 0x400;
  } > ROM

In main_A.c:

volatile char __attribute__((section(".header"))) image_header[0x400];

# Customizing 

There are certain features that will require manual configuration if custom keys wish to be used.

The keys.c file used was generated with the following:
https://juullabs-oss.github.io/mcuboot/encrypted_images.html

The applications were signed using imgtool:
https://juullabs-oss.github.io/mcuboot/imgtool.html

---

ChipWhisperer is a trademark of NewAE Technology Inc., registered in the US, Europe, and China.
