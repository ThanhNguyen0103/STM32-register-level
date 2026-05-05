#include "stdint.h"
void W25Q_WriteEnable(void);
uint8_t W25Q_ReadStatus(void);
void W25Q_WaitBusy(void);
void W25Q_Write(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q_Read(uint32_t addr, uint8_t *buffer, uint16_t len);
void W25Q_EraseSector(uint32_t addr);
uint32_t W25Q128_ReadID(void);
