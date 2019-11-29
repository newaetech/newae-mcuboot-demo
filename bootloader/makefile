# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
#
# Makefile for NewAE secure bootloader
#
#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
# This is the name of the compiled .hex file.
TARGET = NEWAE_BL

CRYPTO_TARGET = NONE
CRYPTO_OPTIONS = RSA

# List C source files here.
# Header files (.h) are automatically pulled in.
SRC += main.c serial_abstract.c 
SRC += dummy_nv_counters.c boot_record.c
SRC += security_cnt.c loader.c  flash_map.c Driver_Flash.c image_validate.c keys.c image_rsa.c bootutil_misc.c 

#FUNC_SEL = NONE
# -----------------------------------------------------------------------------

#CFLAGS += -D$(FUNC_SEL)
CFLAGS += --specs=nosys.specs #this stubs IO calls such as printf 

CLFLAGS += --with-system-zlib
CFLAGS+ = -std=c99  #use c99 dialect

#TODO: get this working as a standalone
#TFMPATH = trusted_firmware_src
#include $(TFMPATH)/Makefile.tfm

MBEDTLS_PATH = ../mbedtls
MBED_CRYPTO_PATH = ../mbed-crypto
#include $(MBEDTLS_PATH)/Makefile
#include $(MBED_CRYPTO_PATH)/Makefile

#Add necessary chip whisperer files to project build
FIRMWAREPATH = ../chipwhisperer/hardware/victims/firmware
include $(FIRMWAREPATH)/crypto/Makefile.mbedtls
include $(FIRMWAREPATH)/crypto/Makefile.crypto
include $(FIRMWAREPATH)/simpleserial/Makefile.simpleserial
include $(FIRMWAREPATH)/Makefile.inc

