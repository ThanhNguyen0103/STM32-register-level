/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private function prototypes -----------------------------------------------*/
void UART_Send_Char(char c);
void UART_Send_String(char *str);

void UART_Read_String(char *str, int i);

/*-------------------------*/
void UART_Send_String(char *str) {

  while (*str) {
    UART_Send_Char(*str++);
  }
}
void UART_Send_Char(char c) {

  while ((USART1->SR & USART_SR_TXE) == 0)
    ;
  USART1->DR = c;
}
void UART_Read_String(char *buf, int len) {
  int i = 0;

  while (i < len - 1) {
    while ((USART1->SR & USART_SR_RXNE) == 0)
      ;

    buf[i] = USART1->DR & 0xFF;

    if (buf[i] == '\r' || buf[i] == '\n')
      break;

    i++;
  }
  buf[i] = '\0';

}

/* ================= MAIN ================= */;
int main(void) {

  //	APB2 peripheral clock enable register (RCC_APB2ENR)
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // port A
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // uart 1
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  //	Port configuration register high (GPIOx_CRH) (x=A..G)

  GPIOA->CRH &= ~(0xF << 4); // output pa9
  GPIOA->CRH |= (0x9 << 4);

  GPIOA->CRH &= ~(0xF << 8); // input pa10
  GPIOA->CRH |= (0x4 << 8);  // Input floating
                             //	UART
  USART1->CR1 = 0;
  USART1->CR2 = 0;

  USART1->CR1 &= ~USART_CR1_M;
  USART1->CR1 &= ~USART_CR1_PCE;

  USART1->CR1 |= USART_CR1_TE;
  USART1->CR1 |= USART_CR1_RE;

  USART1->CR2 &= ~(0x3 << 12);

  USART1->BRR = (52 << 4) | 1;
  USART1->CR1 |= USART_CR1_UE;
  char output[8];
  while (1) {
    UART_Read_String(output, 9);
    UART_Send_String(output);
  }
}
