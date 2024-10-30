#include "APS6404L.h"

#define READ  0x03  // Read instruction for SPI RAM
#define WRITE 0x02  // Write instruction for SPI RAM
#define READ_ID 0x9F  // Instruction to read ID

// Constructor to set the CS pin
APS6404L_Ram::APS6404L_Ram(int csPin) {
  _csPin = csPin;
}

// Initialize SPI and set the chip select pin as output
void APS6404L_Ram::begin() {
  pinMode(_csPin, OUTPUT);
  deselect();  // Make sure the RAM chip is not selected initially
  SPI.begin(); // Initialize SPI
}

// Write a single byte to a specific address
void APS6404L_Ram::writeByte(uint32_t address, uint8_t data) {
  select();
  SPI.transfer(WRITE); // Send write instruction

  // Send the 24-bit address (most SPI RAMs use 24-bit addressing)
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);

  // Send the data byte to write
  SPI.transfer(data);
  deselect();
}

// Write multiple bytes to SPI RAM
void APS6404L_Ram::writeData(uint32_t address, const uint8_t* data, size_t length) {
  select();
  SPI.transfer(WRITE); // Send write instruction

  // Send the 24-bit address
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);

  // Send the data bytes
  for (size_t i = 0; i < length; i++) {
    SPI.transfer(data[i]);
  }

  deselect();
}

// Read a single byte from a specific address
uint8_t APS6404L_Ram::readByte(uint32_t address) {
  select();
  SPI.transfer(READ); // Send read instruction

  // Send the 24-bit address
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);

  // Read the byte from the RAM
  uint8_t result = SPI.transfer(0x00);
  deselect();

  return result;
}

// Read multiple bytes from SPI RAM
void APS6404L_Ram::readData(uint32_t address, uint8_t* buffer, size_t length) {
  select();
  SPI.transfer(READ); // Send read instruction

  // Send the 24-bit address
  SPI.transfer((address >> 16) & 0xFF);
  SPI.transfer((address >> 8) & 0xFF);
  SPI.transfer(address & 0xFF);


  // Read the data bytes
  for (size_t i = 0; i < length; i++) {
    buffer[i] = SPI.transfer(0x00);
  }

  deselect();
}

// Helper function to select the SPI RAM chip (pull CS low)
void APS6404L_Ram::select() {
  digitalWrite(_csPin, LOW);
}

// Helper function to deselect the SPI RAM chip (pull CS high)
void APS6404L_Ram::deselect() {
  digitalWrite(_csPin, HIGH);
}

// Populates the chip ID information
boolean APS6404L_Ram::readChipID() {
  // zero out MFID
  MFID = 0;
  
  select();
  SPI.transfer(READ_ID); // Send the "Read ID" instruction
  // Need to follow that with 3 address bytes
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);

  // ID is described in doco as MFID (8 bits),KGD (8 bits) and 48 bits of EID
  MFID = SPI.transfer(0);
  KGD = SPI.transfer(0);
  // Read the EID, which is next 6 bytes
  for(int i=0 ; i< 6 ; i++){
    EID = (EID <<8) | SPI.transfer(0);
  }
  deselect();

  // If we have a value in MFID, signal success
  if(MFID == 0){
    return false;
  }
  else{
    return true;
  }
}
