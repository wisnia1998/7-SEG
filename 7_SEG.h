#include "PIT_timer.h"									//PIT configruration header
#include "MKL25Z4.h"                    // Device header

/*Pin segment declaration*/
#define SEG_A		(1UL<<30)
#define SEG_B		(1UL<<29)
#define SEG_C		(1UL<<23)
#define SEG_D		(1UL<<22)
#define SEG_E		(1UL<<21)
#define SEG_F		(1UL<<20)
#define SEG_G		(1UL<<5)
#define DP			(1UL<<4)

#define LED1		(1UL<<8)
#define LED2		(1UL<<9)
#define	LED3		(1UL<<10)
#define LED4		(1UL<<11)

#define DOT 10

#define LED_MASK LED1 | LED2 | LED3 | LED4
#define SEG_MASK SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | DP
/*Array of number to display*/
static uint8_t num_to_disp[5] ={
	1,																				//1st digit
	2,																				//2nd digit
	3,																				//3rd digit
	4,																				//4th digit
	0b00000000																//dot position
};

/*Function*/
void _7seg_init(void);
void _7seg_update(uint8_t position, uint8_t number, uint8_t dot_place);
//void _set_transistor(uint8_t position, uint8_t number);
//void _set_number(uint8_t number);
void _dot(void);
void _set_dot(uint8_t dot);
void _set_value(uint16_t value, uint8_t dot);
void _calculate(float val);
