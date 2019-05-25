#ifndef  __SMG_H_
#define  __SMG_H_

#include "sys.h"

//74HC138
#define  HC138_A    PCout(3)
#define  HC138_B    PCout(4)
#define  HC138_C    PCout(5)

//74HC595
#define  SI     PCout(0)
#define  RCK    PCout(1)
#define  SCK    PCout(2)


extern uint8_t smg_data[8];

void SMG_Init(void);
void HC595_Send(uint8_t dat);
void SMG_Sele(uint8_t index);
void SMG_Display(void);

#endif
