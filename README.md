# APS6404L-Library
Arduino library for the APS6404L RAM chip using SPI

# Note - not widely tested. Has been successfully used on AVR microcontrollers using the megaTinyCore (attiny1614) and DxCore (avr128da48)

Very simple library for the APS6404L RAM chip.

I needed a mechanism to buffer substantial (well, relative for a microcontroller) data to allow high speed capture of sensor information.

The APS6404L is easy to use and comes in a suitable form factor. My projects are using the 64Mbit version.

Methods in the library include:
begin() - initialises the code
readByte() - reads a single byte from an address
writeByte() - writes a single byte to an address
readData() - reads multiple bytes from an address
writeData() - writes multiple bytes to an address
readChipID() - reads the chip ID information, populating fields in the object. Returns true if successful
