#include "7_SEG.h"

//number structure define
	//   -- A --
	//  |       |
	//  F       B
	//  |       |
	//   -- G --
	//  |       |
	//  E       C
	//  |       |
	//   -- D --	.DP
 int number_seg[] = {
	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F),	//0
	(SEG_B|SEG_C),																								//1
	(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G),															//2
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G),															//3
	(SEG_B|SEG_C|SEG_F|SEG_G),																		//4
	(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G),															//5
	(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),												//6
	(SEG_A|SEG_B|SEG_C|SEG_F),																		//7
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),									//8
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),												//9
	(DP)																													//DP(10)
	//0xff											//11
};
 int LED [] ={
	 LED1,
	 LED2,
	 LED3,
	 LED4
 };


 
void _7seg_init(void){
	
	SIM -> SCGC5 |= SIM_SCGC5_PORTE_MASK;		//PORTE clock enable
	PORTE -> PCR[4] = PORT_PCR_MUX(1UL);		//SEG A
	PORTE -> PCR[5] = PORT_PCR_MUX(1UL);		//SEG B
	PORTE -> PCR[20] = PORT_PCR_MUX(1UL);		//SEG C
	PORTE -> PCR[21] = PORT_PCR_MUX(1UL);		//SEG D
	PORTE -> PCR[22] = PORT_PCR_MUX(1UL);		//SEG E
	PORTE -> PCR[23] = PORT_PCR_MUX(1UL);		//SEG F
	PORTE -> PCR[29] = PORT_PCR_MUX(1UL);		//SEG G
	PORTE -> PCR[30] = PORT_PCR_MUX(1UL);		//SEG H
	PORTE -> PCR[3] = PORT_PCR_MUX(1UL);		//DP
	PTE -> PDDR |= SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | DP;	//Set as output
	
	SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;		//PORTB clock enable
	PORTB -> PCR[8] = PORT_PCR_MUX(1UL);		//LED1
	PORTB -> PCR[9] = PORT_PCR_MUX(1UL);		//LED2
	PORTB -> PCR[10] = PORT_PCR_MUX(1UL);		//LED3
	PORTB -> PCR[11] = PORT_PCR_MUX(1UL);		//LED4
	PTB -> PDDR |= LED1 | LED2 | LED3 | LED4;	//Set as output
	
	PIT_init();
	
}


void _7seg_update(uint8_t position, uint8_t number, uint8_t dot_place){
	//_set_transistor(position, number);
	PTB -> PCOR |= LED1 | LED2 | LED3 | LED4;	//Turn trasnistor(LED display) OFF
	PTE -> PSOR |= SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | DP;	//Turn segments OFF
	PTE -> PCOR |= number_seg[number];			//segments set
	if(dot_place & 0b0001) {_dot();}									//set dot segment
	PTB -> PSOR |= LED[position];						//Turn selected display

}


/*void _set_transistor(uint8_t position, uint8_t number){
	
	PTB -> PCOR |= LED1 | LED2 | LED3 | LED4;	//Turn trasnistor(LED display) OFF
	PTE -> PSOR |= SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | DP;	//Turn segments OFF
	_set_number(number);
	PTB -> PSOR |= LED[position];						//Turn selected display

}

/*void _set_number(uint8_t number){
	
	PTE -> PCOR |= number_seg[number];			//segments set
}*/

void _dot(){
	PTE -> PCOR |= DP;											//DOT set function
}

void _set_dot(uint8_t dot){
		num_to_disp[4]=dot;
}

void _set_value(uint16_t value, uint8_t dot){
	num_to_disp[3]=value%10;
	value = value/10;
	num_to_disp[2]=value%10;
	value=value/10;
	num_to_disp[1]=value%10;
	value=value/10;
	num_to_disp[0]=value;
	num_to_disp[4]=dot;
}

void _calculate(float val){
	uint8_t dots=0;
	uint16_t mult=1;
	if ((val/1000 < 1) && (val/1000 >= 0.1)) { dots = 4; mult = 10;}
	if ((val/1000 < 0.1) && (val/1000 >= 0.01)) { dots = 2; mult = 100;}
	if ((val/1000 < 0.01)) { dots = 1; mult = 1000;}
	_set_value(val*mult,dots);
}

void PIT_IRQHandler(void)										//PIT interrupt handler function
{
	static	uint16_t i = 0;
	uint8_t dp = num_to_disp[4];							//dot position
	_7seg_update(i,num_to_disp[i],dp >> i);		//7seg update
	i++;																			//increment display position
	if(4 == i) {i=0;}

	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;						//Clear PIT0 falg
}
