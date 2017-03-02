TOPDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

BINARY		= main

DEVICE		= stm32f103c8t6

TOOLCHAIN_DIR	= ../libopencm3

TARGET		= STM32F1

CROSS_PREFIX	?= arm-none-eabi-
CC		= $(CROSS_PREFIX)gcc
OBJCOPY		= $(CROSS_PREFIX)objcopy
SIZE		= $(CROSS_PREFIX)size

CFLAGS		= -Wall -Wextra -std=gnu99 -I../libopencm3/include -I../lib -I ../common -D$(TARGET) -mcpu=cortex-m3 -mthumb -fno-common -ffreestanding -Og -o 0 -g
LDSCRIPT	?= stm32-h103.ld
LDFLAGS		= -lopencm3_stm32f1 -L../libopencm3/lib  -mthumb -mcpu=cortex-m3 -nostartfiles -Wl,--gc-sections -flto -T $(LDSCRIPT)
OBJ		= $(BINARY).o armspi.o

all: $(BINARY).bin

$(BINARY).elf: $(OBJ)
	$(CC) -o $(BINARY).elf $^ $(LDFLAGS)
	$(SIZE) -B $(BINARY).elf

%.bin: %.elf
	$(OBJCOPY) -O binary $^ $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

flash: $(BINARY).bin
	echo "reset halt; flash write_image erase unlock $(TOPDIR)$(BINARY).bin 0x8000000; reset" | nc 127.0.0.1 4444

clean:
	rm -f *.o $(BINARY).elf $(BINARY).bin

debug:
	arm-none-eabi-gdb  -ex 'target extended-remote :3333' $(BINARY).elf

.PHONY: all flash clean debug
