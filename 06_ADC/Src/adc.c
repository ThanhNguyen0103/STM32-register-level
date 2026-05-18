#include "register.h"

void ADC_Init(void) {

  RCC->APB2ENR |= (1 << 2);
  RCC->APB2ENR |= (1 << 9);

  GPIOA->CRL &= ~(0xF << 4);

  ADC1->SQR3 = 1;
  ADC1->SMPR2 |= (7 << 3);

  ADC1->CR2 |=  (1 << 0); // cont , adon

  for (volatile int i = 0; i < 10000; i++)
    ;

  // // calibration
  // ADC1->CR2 |= (1 << 3);
  // while (ADC1->CR2 & (1 << 3))
  //   ;

  // ADC1->CR2 |= (1 << 2);
  // while (ADC1->CR2 & (1 << 2))
  //   ;
  // // ADON
  ADC1->CR2 |= (1 << 0);
}
uint16_t ADC_Read(void) {
  
  while (!(ADC1->SR & (1 << 1)));
  return ADC1->DR;
}