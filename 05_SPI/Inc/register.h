#pragma once
#include <stdint.h>

/* GPIO */
typedef struct {
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

/* RCC */
typedef struct {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
} RCC_TypeDef;

/* UART */
typedef struct {
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t CTPR;
} USART_TypeDef;

/* AF */
typedef struct {
  // 0x4001 0000
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;

} AFIO_TypeDef;

/* I2C */
typedef struct {
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t DR;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t CCR;
  volatile uint32_t TRISE;

} I2C_TypeDef;

/* SPI */
typedef struct {
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t CRCPR;
  volatile uint32_t RXCRCR;
  volatile uint32_t TXCRCR;
  volatile uint32_t I2SCFGR;
} SPI_TypeDef;

/*=================================*/

/* RCC */
#define RCC ((RCC_TypeDef *)0x40021000UL)
/* GPIO */
#define GPIOA ((GPIO_TypeDef *)0x40010800UL)
#define GPIOC ((GPIO_TypeDef *)0x40011000UL)
#define GPIOB ((GPIO_TypeDef *)0x40010C00UL)
/* AFIO */
#define AFIO ((AFIO_TypeDef *)0x40010000UL)
/* USART */
#define USART1 ((USART_TypeDef *)0x40013800UL)
/* I2C1*/
#define I2C1 ((I2C_TypeDef *)0x40005400UL)
/* SPI */
#define SPI1 ((SPI_TypeDef *)0x40013000UL)

/*===================*/
#define NVIC_ISER1 (*(volatile unsigned int *)0xE000E104)
#define NVIC_ISER0 (*(volatile unsigned int *)0xE000E100)
/* */
#define USART1_IRQn 37
/* */
#define I2C1_EV_IRQn = 31
#define I2C1_ER_IRQn = 32
