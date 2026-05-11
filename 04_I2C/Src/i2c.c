#include "register.h"
#include <stdint.h>

void I2C_Init(void) {
  RCC->APB1ENR |= (1 << 21); //  I2C 1 clock enable
  RCC->APB2ENR |= (1 << 3);  // Port B

  GPIOB->CRL &= ~((0xD << 24) | (0xD << 28));
  GPIOB->CRL |= (0xD << 24) | (0xD << 28);

  //
  I2C1->CR2 = 8;   // freq
  I2C1->CCR = 40;  //
  I2C1->TRISE = 9; // trise
  //
  I2C1->CR1 |= (1 << 0); // enable i2c
}

void I2C_Start(void) {
  I2C1->CR1 |= (1 << 8);
  while ((I2C1->SR1 & (1 << 0)) == 0)
    ;
}
void I2C_SendAddr(uint8_t addr) {
  I2C1->DR = (addr << 1);
  while ((I2C1->SR1 & (1 << 1)) == 0)
    ;
  (void)I2C1->SR2;
}
void I2C_Tx(uint8_t data) {
  while ((I2C1->SR1 & (1 << 7)) == 0)
    ;
  I2C1->DR = data;

  while ((I2C1->SR1 & (1 << 2)) == 0)
    ;
}
void I2C_Stop(void) { I2C1->CR1 |= (1 << 9); }