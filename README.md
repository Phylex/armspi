# ARMSPI, a packet based library for the stm32f103 SPI module.
## General struckture and scope
The library provides a packet based approach to SPI, it enables the user to write a packet into a buffer of packets preallocated in SRAM that is then sent automatically of via SPI.
This process is entirely interrupt based to minimize CPU Time used.
The packet consists of the data to be transmitted and a number, denoting its length.
The maximum length of the Packet must be given at compiletime.
The Buffer is implemented as a ringbuffer, the size of wich must be given at compiletime.

The recieving side is implemented as a LIFO buffer (ringbuffer), that overwrites the still unread packets if it is full, by incrementing the readout pointer to be at least the write pointer.
The length of the recieving buffer must also be given at compiletime.

## Interface
The interface consits of:
*`init_SPI(baud)`
   initialises SPI, configuring clock and SPI interface. The baudrate is given and mached as good as possible using the prescalars available in the hardware.
*`write_SPI( data )`
   writes the data given as argument into a packet in the send buffer.
*`read_SPI()`
   reads the next packet from the input buffer and returns it.

The Library needs some information at compiletime:
*`PACKETLENGTH`
   length of a packet
*`TRANSMITBUFFERLENGTH`
   Number of packets in the send buffer
*`RECIEVEBUFFERLENGTH`
   Number of packets in the recieve buffer
