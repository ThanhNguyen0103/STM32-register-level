#include "stdint.h"
void I2C_Init(void);
void I2C_Start(void) ;
void I2C_SendAddr(uint8_t addr);
void I2C_Tx(uint8_t data) ;
void I2C_Stop(void) ;

