#include "spi.h"
#include <stdint.h>

void W25Q_WriteEnable(void) {
  CS_LOW();
  SPI_Tx(0x06); // Write Enable
  CS_HIGH();
}
uint8_t W25Q_ReadStatus(void) {
  uint8_t status;
  CS_LOW();
  SPI_Tx(0x05);          // Read Status
  status = SPI_Rx(); // dummy read
  CS_HIGH();
  return status;
}

void W25Q_WaitBusy(void) {
  while (W25Q_ReadStatus() & 0x01)
    ;
}
void W25Q_Write(uint32_t addr, uint8_t *data, uint16_t len) {
  W25Q_WriteEnable();
  CS_LOW();

  SPI_Tx(0x02); // Page Program

  SPI_Tx((addr >> 16) & 0xFF);
  SPI_Tx((addr >> 8) & 0xFF);
  SPI_Tx(addr & 0xFF);

  for (int i = 0; i < len; i++) {
    SPI_Tx(data[i]);
  }

  CS_HIGH();

  W25Q_WaitBusy();
}
void W25Q_Read(uint32_t addr, uint8_t *buffer, uint16_t len) {
  CS_LOW();

  SPI_Tx(0x03); // Read Data

  // gửi địa chỉ
  SPI_Tx((addr >> 16) & 0xFF);
  SPI_Tx((addr >> 8) & 0xFF);
  SPI_Tx(addr & 0xFF);

  // đọc data
  for (int i = 0; i < len; i++) {
    SPI_Tx(0xFF);
    buffer[i] = SPI_Rx(); // dummy để nhận data
  }

  CS_HIGH();
}
void W25Q_EraseSector(uint32_t addr) {
  W25Q_WriteEnable();

  CS_LOW();

  SPI_Tx(0x20); // Sector Erase (4KB)

  SPI_Tx((addr >> 16) & 0xFF);
  SPI_Tx((addr >> 8) & 0xFF);
  SPI_Tx(addr & 0xFF);

  CS_HIGH();

  W25Q_WaitBusy();
}

uint32_t W25Q128_ReadID(void) {
  uint32_t device_id = 0;
  uint8_t m_id, mt_id, c_id;
  CS_LOW();

  SPI_Tx(0x9F);

  m_id = SPI_Rx();  // Manufacturer ID
  mt_id = SPI_Rx(); // Memory Type
  c_id = SPI_Rx();  // Capacity ID

  CS_HIGH();
  device_id = (m_id << 16) | (mt_id << 8) | (c_id);

  return device_id;
}
