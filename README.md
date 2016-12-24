# ARMSPI, a packet based library for the stm32f103 SPI module.
## General struckture and scope
The library provides a packet based approach to SPI, it enables the user to write a packet into a buffer of packets preallocated in SRAM that is then sent automatically of via SPI.
This process is entirely interrupt based to minimize CPU Time used.
The packet consists of the data to be transmitted and a number, denoting its length.
The maximum length of the Packet must be given at compiletime.
The Buffer is implemented as a ringbuffer, the size of wich must be given at compiletime.

The recieving side is implemented as a LIFO buffer (ringbuffer), that overwrites the still unread packets if it is full, by incrementing the readout pointer to be at least the write pointer.
The length of the recieving buffer must also be given at compiletime.

The State of the buffer is captured and displayed for all involved functions through a status register that is named `spi_status` it is only altered by the functions within the library, but for sake of completeness I thought I should mentione it here.

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

* `write_SPI(*data, size)`

    writes the data given as argument into a packet in the send buffer.

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

## The handling of Slaves
This library is generally capable of handling multiple Slaves. Therefore the SSM on the STM's is enabled. To enable a second slave, define the port and pin and in the header everything else should be done at compiletime. every other port and pin definition schould be commented out.
If using more than 5 Slaves, one has to edit the armspi.c file and add another line in the initialisations of the `connected_slaves_(modulenumber)` in the same manner the others have been added.
The naming convention should be fairly obvious and I recomment do follow it.
The Naming convention is as follows:
In `SPI_N_SLAVE_M_[PORT/PIN]` the N denotes the number of the Module and the M denotes the number of the Slave connected.

## Iterrupt handling
The data and is mostly hadeled within the interrupt routine. This checks the state of the packet in the status register and then manipulates the data accordingly, eighther sending the next byte of data,
selecting the next paket for sending or shutting down the clock because the buffer is empty.

## Indices and general I/O procedures
The software is esentially a piece of data management software put ontop of a hardware interface. For the routines used to access the data I chose the scheme that consists of the following elements:
* Check

    We check if the position, that the pointer is pointing to is valid, if so we can go to the next step, if not, we set appropriate flags.

* Read/Write

    Read/Write the output/input into the data structures, if the checks returned with the goahead

Because of the Structure of a Ringbuffer, there are a few cases where design decisions have to be made.
* `HEAD` catches up with `TAIL`:

   when this happenes, the position of the `TAIL` is rotated further by one position, the freed packet is overwritten in the process.
   If `HEAD` and `TAIlL` are at the same position the buffer empty flag is set.

* Interpretation of the `HEAD` pointer:

   The head pointer points to the packet, that is written to by the hardware. This means, that the first readable packet is `HEAD-1`. If the `TAIL` is at the same position as Head the tail returns a 0 and sets the BUFFER_EMPTY Flag
