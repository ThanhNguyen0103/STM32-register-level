#include "spi.h"
#include <stdint.h>

void W25Q_WriteEnable(void) {
  CS_LOW();
  SPI_TxRx(0x06); // Write Enable
  CS_HIGH();
}
uint8_t W25Q_ReadStatus(void) {
  uint8_t status;
  CS_LOW();
  SPI_TxRx(0x05);          // Read Status
  status = SPI_TxRx(0xFF); // dummy read
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

  SPI_TxRx(0x02); // Page Program

  SPI_TxRx((addr >> 16) & 0xFF);
  SPI_TxRx((addr >> 8) & 0xFF);
  SPI_TxRx(addr & 0xFF);

  for (int i = 0; i < len; i++) {
    SPI_TxRx(data[i]);
  }

  CS_HIGH();

  W25Q_WaitBusy();
}
void W25Q_Read(uint32_t addr, uint8_t *buffer, uint16_t len) {
  CS_LOW();

  SPI_TxRx(0x03); // Read Data

  // gửi địa chỉ
  SPI_TxRx((addr >> 16) & 0xFF);
  SPI_TxRx((addr >> 8) & 0xFF);
  SPI_TxRx(addr & 0xFF);

  // đọc data
  for (int i = 0; i < len; i++) {
    buffer[i] = SPI_TxRx(0xFF); // dummy để nhận data
  }

  CS_HIGH();
}
void W25Q_EraseSector(uint32_t addr) {
  W25Q_WriteEnable();

  CS_LOW();

  SPI_TxRx(0x20); // Sector Erase (4KB)

  SPI_TxRx((addr >> 16) & 0xFF);
  SPI_TxRx((addr >> 8) & 0xFF);
  SPI_TxRx(addr & 0xFF);

  CS_HIGH();

  W25Q_WaitBusy();
}

uint32_t W25Q128_ReadID(void) {
  uint32_t device_id = 0;
  uint8_t m_id, mt_id, c_id;
  CS_LOW();

  SPI_TxRx(0x9F);

  m_id = SPI_TxRx(0x00);  // Manufacturer ID
  mt_id = SPI_TxRx(0x00); // Memory Type
  c_id = SPI_TxRx(0x00);  // Capacity ID

  CS_HIGH();
  device_id = (m_id << 16) | (mt_id << 8) | (c_id);

  return device_id;
}
