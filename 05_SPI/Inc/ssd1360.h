

#include "stdint.h"
void OLED_Init(void);

void OLED_Reset(void);
void OLED_SendCommand(uint8_t cmd);
void OLED_SendData(uint8_t data);

void OLED_Fill(void);
void OLED_WriteChar(unsigned char c);
void OLED_WriteString(unsigned char *c);