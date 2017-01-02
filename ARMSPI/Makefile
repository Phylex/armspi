TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BINARY		= armspi

DEVICE		= stm32f103c8t6

TOOLCHAIN_DIR	= ../libopencm3

TARGET		= DSTM32F1

CROSS_PREFIX	?= arm-none-eabi-
CC		= $(CROSS_PREFIX)gcc
OBJCOPY		= $(CROSS_PREFIX)objcopy
SIZE		= $(CROSS_PREFIX)size

CFLAGS		= -Wall -Wextra -std=gnu99 -I../libopencm3/include -I ../common -$(TARGET) -mcpu=cortex-m3 -mthumb -fno-common -ffreestanding -Og -g
LDSCRIPT	?= $(BINARY).ld
LDFLAGS		= -lopencm3_stm32f1 -L../libopencm3/lib -mthumb -mcpu=cortex-m3 -nostartfiles -Wl,--gc-sections
OBJ		= $(BINARY).o


all: $(BINARY).bin

include $(TOOLCHAIN_DIR)/ld/Makefile.linker

$(BINARY).elf: $(OBJ)
	$(CC) -o armspi.elf $^ $(LDFLAGS)
	$(SIZE) -B armspi.elf

%.bin: %.elf
	$(OBJCOPY) -O binary $^ $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

flash: $(BINARY).bin
	echo "reset halt; flash write_image erase unlock $(TOPDIR)/armspi.bin 0x8000000; reset" | nc 127.0.0.1 4444

clean:
	rm -f *.o $(BINARY).elf $(BINARY).bin

debug:
	arm-none-eabi-gdb  -ex 'target extended-remote :3333' $(BINARY).elf

.PHONY: all flash clean debug
