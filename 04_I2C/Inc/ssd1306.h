#include <stdint.h>

void OLED_SendCommand(uint8_t *cmd , uint8_t len) ;
void OLED_SendData(uint8_t data);
void OLED_WriteChar(unsigned char c);
void OLED_WriteString(unsigned char *c);

