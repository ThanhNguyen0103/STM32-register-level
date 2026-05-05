
#include "register.h"
#include <stdint.h>

#define CS_LOW() (GPIOA->ODR &= ~(1 << 4))
#define CS_HIGH() (GPIOA->ODR |= (1 << 4))

#define DC_CMD() (GPIOA->ODR &= ~(1 << 2))
#define DC_DATA() (GPIOA->ODR |= (1 << 2))

#define RES_LOW() (GPIOA->ODR &= ~(1 << 3))
#define RES_HIGH() (GPIOA->ODR |= (1 << 3))
void SPI1_Init(void);
uint8_t SPI_TxRx(uint8_t data);
