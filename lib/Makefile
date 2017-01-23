LIBRARY		= libarmspi

TOOLCHAIN_DIR	= ../libopencm3

TARGET		= STM32F1

CROSS_PREFIX	?= arm-none-eabi-
CC		= $(CROSS_PREFIX)gcc
OBJCOPY		= $(CROSS_PREFIX)objcopy
SIZE		= $(CROSS_PREFIX)size
AR		= $(CROSS_PREFIX)ar

CFLAGS		= -Wall -Wextra -std=gnu99 -I../libopencm3/include -I ../common -D$(TARGET) -mcpu=cortex-m3 -mthumb -fno-common -ffreestanding -Og -g
OBJ		= $(LIBRARY).o

all: $(LIBRARY).a

$(LIBRARY).a: $(OBJ)
	$(AR) -crs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o $(LIBRARY).a

.PHONY: all clean
