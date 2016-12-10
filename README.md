# ARMSPI, a packet based library for the stm32f103 SPI module.
## General struckture and scope
The library provides a packet based approach to SPI, it enables the user to write a packet into a buffer of packets preallocated in SRAM that is then sent automatically of via SPI.
This process is entirely interrupt based to minimize CPU Time used.
The packet consists of the data to be transmitted and a number, denoting its length.
The maximum length of the Packet must be given at compiletime.
The Buffer is implemented as a ringbuffer, the size of wich must be given at compiletime.

The recieving side is implemented as a LIFO buffer (ringbuffer), that overwrites the still unread packets if it is full, by incrementing the readout pointer to be at least the write pointer.
The length of the recieving buffer must also be given at compiletime.

The State of the buffer is captured and displayed for all involved functions through a status register that is named `spi_status` it is only altered by the functions within the library, but for sake of completeness I thought to mentione it here.

The mode of the software (master/slave) is set by defining `MASTER` if the device should run as master and `SLAVE` if the device should run as slave.

## Interface
The interface consits of:
* `init_SPI(baud)`

    initialises SPI, configuring clock and SPI interface. The baudrate is given and mached as good as possible using the prescalars available in the hardware.

* `write_SPI(data)`

    writes the data given as argument into a packet in the send buffer.

* `read_SPI()`

    reads the next packet from the input buffer and returns it.

The Library needs some information at compiletime:
* `PACKETLENGTH`

    length of a packet

* `TRANSMITBUFFERLENGTH`

    Number of packets in the send buffer

* `RECIEVEBUFFERLENGTH`

    Number of packets in the recieve buffer

## Data Structures
The main data Structure is the Packet struct. It consists of an array, that has the length `PACKETLENGTH`, measured in bytes, and a `uint8_t` that denotes the size. the Size 0 denotes that packet is empty.

## Iterrupt handling
The data and is mostly hadeled within the interrupt routine. This checks the state of the packet in the status register and then manipulates the data accordingly, eighther sending the next byte of data,
selecting the next paket for sending or shutting down the clock because the buffer is empty.


