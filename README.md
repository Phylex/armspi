# ARMSPI, a packet based library for the stm32f103 SPI module.
## General struckture and scope
The library provides a packet based approach to SPI, it enables the user to write a packet into a buffer of packets preallocated in SRAM that is then sent automatically of via SPI.
This process is entirely interrupt based to minimize CPU Time used.
The maximum length of the Packet must be given at compiletime.
The Buffer is implemented as a ringbuffer, the size of wich must be given at compiletime.

The recieving side is implemented as a FIFO buffer (ringbuffer), that overwrites the still unread packets if it is full, by incrementing the readout pointer to be at least the write pointer.
The length of the recieving buffer must also be given at compiletime.

The State of the buffer is captured and displayed for all involved functions through a status register that is named `spi_status` it is only altered by the functions within the library, but for sake of completeness I thought I should mentione it here.

Please Note, that the Clock is not manipulated anywhere in the Library, because of the wide variations of clock tree configurations and quartz frequencie. This is why it is left to the User, to provide the activated SPI modules with needed Clock inputs.
The only thing needed to be done is to provide the SPI module in question with the desired clock. Please be aware of possible clocking differences in master and Slave mode.

## Data Structures
The data structure consists of Packets, the size of which can be determined py `PACKETLENGTH`.
These are then organized into a Ringbuffer.
The leading Pointer of the Ringbuffer is the `HEAD` and the trailing one is the `TAIL`.
Two ringbuffer are then combined to make a spi-module.
The Spi-Module also incorporates a Status byte and the connected slaves.
The Pins that the slaves are connected to are given another struct called PIN. It consists of a pointer to the Memory mapped address of the port plus the pin number within that port.
The Data for the address of the pins and ports is taken from the headers provided by the libopencm3 Project.

## Interface
The interface consits of:
* `init_SPI()`

    initialises SPI, configuring clock and SPI interface. The baudrate is given and mached as good as possible using the prescalars available in the hardware.
    To calculate the speed at wich the Clock of the SPI has to be set to nearest mach the bauderate given it will read the setting from the RCC unit

* `uint8_t write_SPI(*data, size)`

    writes the data given as argument into a packet in the send buffer. This funktion clears the tail of the txbuffer if they collide even if it is in the process of being sent. (double buffering is planned at one point). The interrupt then assumes that the packet has been sent entirely and proceeds to the next. So make sure that the rate of data to be sent does not surpass the confiigured data output.

* `read_SPI()`

    reads the next packet from the input buffer and returns it.

* `set_SPI_mode(spi_module, mode)`

    This sets the Mode of the SPI-device into master or slave mode. When this is done the current packet in the recieve and send buffers are dropped and the buffers are rotated to the next packet.

The Library needs some information at compiletime:
* `PACKETLENGTH`

    length of a packet

* `TRANSMITBUFFERLENGTH`

    Number of packets in the send buffer

* `RECIEVEBUFFERLENGTH`

    Number of packets in the recieve buffer

* `SPI_MODULE_0`, `SPI_MODULE_1`, `SPI_MODULE_2`, `SPI_MODULE_3`, `SPI_MODULE_4`, `SPI_MODULE_5`

    The Module that should be activated has to be defined, therefor the the Module name has to be uncommented in armspi.h
    The Module name here corresponds to the hardware interface of the number (modulenumber +1).
    It includes the default pins for that device as defined in the libopencm3 for that device.

##Usage
The spimodules named spi_module_[0-5] must be declared as external variables as they are decared inside the armspi.c file.
After that the fuctions of the module can be used as normal.

## The handling of Slaves
This library is generally capable of handling multiple Slaves.
Every module points to an array of hardware_pin structs, that are the SS-Pins that are driven.
Therefore the SSM on the STM's is enabled. To enable a second slave, define the port and pin and in the header everything else should be done at compiletime. every other port and pin definition schould be commented out.
If using more than 5 Slaves, one has to edit the armspi.c file and add another line in the initialisations of the `connected_slaves_(modulenumber)` in the same manner the others have been added to the code.
The naming convention should be fairly obvious and I recomment do follow it.
The Naming convention is as follows:
In `SPI_N_SLAVE_M_[PORT/PIN]` the N denotes the number of the Module and the M denotes the number of the Slave connected.

## Being a Slave
When the chip is set into slave mode, it polls the 0th pin specified in the connected_slaves list of the SPI module in question and if it is pulled low the SPI-Module is swiched on, and recieves the information, stopping and dropping all further bytes if the packet is full and only swiching to the next packet, if the SS line retunes to HIGH and is then pulled low again.

## Iterrupt handling
The data and is mostly hadeled within the interrupt routine. This checks the state of the packet in the status register and then manipulates the data accordingly, eighther sending the next byte of data,
selecting the next paket for sending or shutting down the clock because the buffer is empty.
