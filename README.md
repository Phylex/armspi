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

## Data Structures
The main data Structure is the Packet struct. It consists of an array, that has the length `PACKETLENGTH`, measured in bytes, and a `uint8_t` that denotes the size. the Size 0 denotes that packet is empty.
Derived from the packet data structure is are the two ringbuffer that store the incoming and outgoing packets, until transmission or retrecval or overwrite. The Funktions `write_SPI` and `read_SPI` access those buffers

The user has to (because of the fact that the ringbuffer structs should be declared globally) declare as many spi structs as he has SPI modules. the structure then has to be passed to the

## Interface
The interface consits of:
* `init_SPI(baud)`

    initialises SPI, configuring clock and SPI interface. The baudrate is given and mached as good as possible using the prescalars available in the hardware.
    To calculate the speed at wich the Clock of the SPI has to be set to nearest mach the bauderate given it will read the setting from the RCC unit

* `write_SPI(data)`

    writes the data given as argument into a packet in the send buffer.

* `read_SPI()`

    reads the next packet from the input buffer and returns it.

* `set_SPI_mode(mode)`

    This sets the Mode of the SPI-device into master or slave mode. The corresponding define is `MASTER` and `SLAVE` and these are defined in armspi.h

The Library needs some information at compiletime:
* `PACKETLENGTH`

    length of a packet

* `TRANSMITBUFFERLENGTH`

    Number of packets in the send buffer

* `RECIEVEBUFFERLENGTH`

    Number of packets in the recieve buffer

* `DEVICE_AMOUNT`

    The amount of SPI interfaces that are to be used with the library.

* `SPI_MODULE_0`, `SPI_MODULE_1`, `SPI_MODULE_2`, `SPI_MODULE_3`, `SPI_MODULE_4`, `SPI_MODULE_5`, `SPI_MODULE_6`

    The Module that should be activated has to be defined, therefor the the Module name has to be uncommented in armspi.h

## Iterrupt handling
The data and is mostly hadeled within the interrupt routine. This checks the state of the packet in the status register and then manipulates the data accordingly, eighther sending the next byte of data,
selecting the next paket for sending or shutting down the clock because the buffer is empty.

## Indices and general I/O procedures
The software is esentially a piece of data management software put ontop of a hardware interface. For the routines used to access the data I chose the scheme:
* Check/Redirect

    check if the data at the index is within range of the different data structures and/or allowed ranges and if the IO operation has reached a boundary, redirect it to the proper place in the data structures or terminate the I/O operation

* Read/Write

    Read/Write the output/input into the data structures, if the checks returned with the goahead

* Increment

   Now we simply increment the counter/pointer and terminate the I/O operation

Because of the Structure of a Ringbuffer, there are a few cases where design decisions have to be made.
* `HEAD` catches up with `TAIL`:

   when this happenes, the position of the `TAIL` is rotated further by one position, the freed packet is overwritten in the process.

* Meaning of the `HEAD` pointer:

   The head pointer points to the packet, that is written to by the hardware. This means, that the first readable packet is `HEAD-1`. If the `TAIL` is at the same position as Head the tail returns a 0 and sets the BUFFER_EMPTY Flag
