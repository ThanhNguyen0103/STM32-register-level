#include "register.h"
#include <stdint.h>

void dma_init(void) {
  RCC->AHBENR |= (1 << 0); // DMA1EN

  DMA1_Channel2->CCR = 0;
  DMA1_Channel2->CCR |= (1 << 7);  // MINC
  DMA1_Channel2->CCR &= ~(1 << 6); // PINC = 0
  DMA1_Channel2->CCR &= ~(1 << 4); // DIR = 0 (RX)

  DMA1_Channel3->CCR = 0;
  DMA1_Channel3->CCR |= (1 << 7);  // MINC
  DMA1_Channel3->CCR &= ~(1 << 6); // PINC = 0
  DMA1_Channel3->CCR |= (1 << 4);  // DIR = 1 (TX)
}

void dma_config(uint8_t *src, uint8_t *des, uint8_t len) {

  DMA1_Channel2->CCR &= ~1;
  DMA1_Channel3->CCR &= ~1;

  DMA1_Channel2->CPAR = (uint32_t)&SPI1->DR;
  DMA1_Channel2->CMAR = (uint32_t)des;
  DMA1_Channel2->CNDTR = len;

  DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
  DMA1_Channel3->CMAR = (uint32_t)src;
  DMA1_Channel3->CNDTR = len;
}
void dma_tranfer(void) {
  DMA1_Channel2->CCR |= (1 << 0);
  DMA1_Channel3->CCR |= (1 << 0);
}