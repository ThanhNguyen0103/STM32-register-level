#include "spi.h"
#include "register.h"
#include <stdint.h>

void SPI1_Init(void) {
  // Enable clock
  RCC->APB2ENR |= (1 << 12); // SPI1
  RCC->APB2ENR |= (1 << 0);  // AFIO clock
  RCC->APB2ENR |= (1 << 2);  // GPIOA

  GPIOA->CRL &= ~(0xF << 24); // Clear PA6
  GPIOA->CRL |= (0x4 << 24);  // Set PA6 as Input Floating
  // PA5 (SCK), PA7 (MOSI) -> AF push-pull
  GPIOA->CRL &= ~((0xF << 20) | (0xF << 28));
  GPIOA->CRL |= ((0xB << 20) | (0xB << 28));

  // PA4, PA3, PA2 -> output (CS, DC, RES)
  GPIOA->CRL &= ~((0xF << 16) | (0xF << 12) | (0xF << 8));
  GPIOA->CRL |= ((0x3 << 16) | (0x3 << 12) | (0x3 << 8));

  // SPI config
  SPI1->CR1 = 0;

  SPI1->CR1 |= (1 << 2);            // Master
  SPI1->CR1 |= (0x2 << 3);          // Baud rate /4
  SPI1->CR1 |= (1 << 9) | (1 << 8); // SSM, SSI

  SPI1->CR1 |= (1 << 6); // Enable SPI
  CS_HIGH();
}
uint8_t SPI_TxRx(uint8_t data) {

  while (!(SPI1->SR & (1 << 1)))
    ; // TX empty
  SPI1->DR = data;
  while ((SPI1->SR & (1 << 7)))
    ;

  while (!(SPI1->SR & (1 << 0)))
    ; // RX not empty
  return SPI1->DR;
}