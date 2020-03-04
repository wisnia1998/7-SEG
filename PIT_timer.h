#include "MKL25Z4.h"                    // Device header

#define PIT0_val 80000/3*2 //200Hz
#define PIT_ALARM_INT_NBR (IRQn_Type) 22	//IRQn of PIT

void PIT_init(void);
