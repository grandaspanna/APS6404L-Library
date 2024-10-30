#ifndef APS6404L_H
#define APS6404L_H

#include <Arduino.h>
#include <SPI.h>

class APS6404L_Ram {
  public:

    uint8_t MFID, KGD;
    uint64_t EID; // Note that EID is only 48 bits
    
    // Constructor: Initializes the SPI RAM with a given CS pin
    APS6404L_Ram(int csPin);

    // Initialize the SPI and select the RAM chip
    void begin();

    // Write a byte to a specific address in the SPI RAM
    void writeByte(uint32_t address, uint8_t data);

    // Write multiple bytes to the SPI RAM
    void writeData(uint32_t address, const uint8_t* data, size_t length);

    // Read a byte from a specific address in the SPI RAM
    uint8_t readByte(uint32_t address);

    // Read multiple bytes from the SPI RAM
    void readData(uint32_t address, uint8_t* buffer, size_t length);

    // Function to read the Chip ID
    boolean readChipID(); 

  private:
    int _csPin; // Chip Select pin for SPI RAM

    // Helper function to select/deselect the SPI RAM
    void select();
    void deselect();
};

#endif
