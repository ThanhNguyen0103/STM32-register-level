#include "spi.h"
#include "register.h"

void SPI1_Init(void) {
  // Enable clock
  RCC->APB2ENR |= (1 << 12); // SPI1
  RCC->APB2ENR |= (1 << 0);  // AFIO clock
  RCC->APB2ENR |= (1 << 2);  // GPIOA

  // PA5 (SCK), PA7 (MOSI) -> AF push-pull
  GPIOA->CRL &= ~((0xF << 20) | (0xF << 28));
  GPIOA->CRL |= ((0xB << 20) | (0xB << 28));

  // PA4, PA3, PA2 -> output (CS, DC, RES)
  GPIOA->CRL &= ~((0xF << 16) | (0xF << 12) | (0xF << 8));
  GPIOA->CRL |= ((0x3 << 16) | (0x3 << 12) | (0x3 << 8));

  // SPI config
  SPI1->CR1 = 0;

  SPI1->CR1 |= (1 << 2);            // Master
  SPI1->CR1 |= (1 << 3);            // Baud rate /4
  SPI1->CR1 |= (1 << 9) | (1 << 8); // SSM, SSI

  // CPOL = 0, CPHA = 0 (Mode 0)

  SPI1->CR1 |= (1 << 6); // Enable SPI
}
void SPI_Send(uint8_t data) {
  while (!(SPI1->SR & (1 << 1)))
    ; // TXE
  SPI1->DR = data;
  while (SPI1->SR & (1 << 7))
    ; // BSY
}