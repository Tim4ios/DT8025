# Makefile for Raspberry Pi 3
# Updated by Wagner Morais Oct 22

MAINFILE = a4p1

OBJS	=  lib/expstruct.o lib/piface.o
OBJS	+= lib/uart.o lib/rpi-armtimer.o lib/rpi-gpio.o lib/rpi-interrupts.o lib/rpi-systimer.o 
OBJS	+= lib/tinythreads.o 

OBJS	+= lib/startup.o lib/syscalls.o 
OBJS	+= $(MAINFILE).o

ELF		= $(MAINFILE).elf
MAIN	= $(MAINFILE).img

CROSS	= arm-none-eabi-
CC		= $(CROSS)gcc
AS		= $(CROSS)as
SIZE	= $(CROSS)size
OCOPY	= $(CROSS)objcopy


# CFLAGS	= -march=armv8-a -mcpu=cortex-a53 -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib -DRPI3=1 -DIOBPLUS=1
CFLAGS	= -march=armv8-a+crc -mtune=cortex-a53 -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib -DRPI3=1 -DIOBPLUS=1

LFLAGS	= -static -nostartfiles -lc -lgcc -specs=nano.specs -Wl,--gc-sections -lm
LSCRIPT	= lib/rpi3.ld

LDFLAGS	+= -u _printf_float

.PHONY: all clean run

all: $(MAIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(ELF): $(OBJS)
	$(CC) -T $(LSCRIPT) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@
	
$(MAIN): $(ELF)
	$(OCOPY) $< -O binary $@

clean:
#   OS dependent. Change accordingly
#	del /Q /F $(MAIN) $(ELF) $(OBJS)
#	rm -f $(MAIN) $(ELF) $(OBJS)

run: $(MAIN)