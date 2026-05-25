#include "register.h"
#include <stdint.h>

void CAN_Init(void) {

  RCC->APB1ENR |= (1 << 25); // CAN1
  RCC->APB2ENR |= (1 << 2);  // GPIOA
  // RCC->APB2ENR |= (1 << 0); // AFIO
  //
  GPIOA->CRH &= ~((0xF << 16) | (0xF << 12));
  GPIOA->CRH |= (0xB << 16) | (0x4 << 12);
  CAN1->MCR |= (1<<5);
  // Initialization mode
  CAN1->MCR |= (1 << 0);
  while ((CAN1->MSR & (1 << 0)) == 0)
    ;

  CAN1->BTR = 0;
  CAN1->BTR |=
      (1 << 30) | // LBKM
      (4 << 20) | // TS2 = 4 tq
      (9 << 16) | // TS1 = 13 tq
      (3 << 0);   // BRP = 5
  // To leave Initialization mode
  CAN1->MCR &= ~(1 << 0);
  while ((CAN1->MSR & (1 << 0)) != 0)
    ;
}

void CAN_Config(void) {
  CAN1->FMR |= (1 << 0);
  CAN1->FA1R &= ~(1 << 0);

  CAN1->FM1R &= ~(1 << 0);
  CAN1->FS1R |= (1 << 0);
  CAN1->FFA1R &= ~(1 << 0);

  CAN1->sFilterRegister[0].FR1 = 0;
  CAN1->sFilterRegister[0].FR2 = 0;
  CAN1->FA1R |= (1 << 0);
  CAN1->FMR &= ~(1 << 0);
}

void CAN_Transfer(void) {
  while (!(CAN1->TSR & (1 << 26)))
    ;

  CAN1->sTxMailBox[0].TIR = 0;
  CAN1->sTxMailBox[0].TIR |= (0x123 << 21);

  //
  CAN1->sTxMailBox[0].TDTR &= ~(0xF);
  CAN1->sTxMailBox[0].TDTR = 1;
  //
  CAN1->sTxMailBox[0].TDLR = 0xAB;
  // CAN1->sTxMailBox[0].TDHR = 0x55667788;

  CAN1->sTxMailBox[0].TIR |= (1 << 0);
  while (!(CAN1->TSR & (1 << 1)))
    ;
}

void CAN_Receive(void) {
  while ((CAN1->RF0R & 0x3) == 0)
    ;
  uint32_t value = CAN1->sFIFOMailBox[0].RIR;

  uint32_t lengt = CAN1->sFIFOMailBox[0].RDTR;
  uint32_t data = CAN1->sFIFOMailBox[0].RDLR;
  // release FIFO
  CAN1->RF0R |= (1 << 5);
}