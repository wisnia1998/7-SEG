#include "MKL25Z4.h"                    // Device header
#include "PIT_timer.h"
#include "7_SEG.h"

int main()
{
	/*SIM -> SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB ->PCR[10] = PORT_PCR_MUX(1UL);
	PTB -> PDDR |= (1UL << 10);*/
	PIT_init();
	_7seg_init();
	__enable_irq();
int i=0;
	while(1)
	{
		_set_value(1234,1);
		for(i=0;i<3000000;i++){}
		_set_value(4321,4);
		for(i=0;i<3000000;i++){}
		_set_value(5533,8);
		for(i=0;i<3000000;i++){}	
		_calculate(1.998);
		for(i=0;i<8000000;i++){}
		_calculate(123.4);
		for(i=0;i<8000000;i++){}
		_calculate(0.11);
		for(i=0;i<8000000;i++){}
		_calculate(1111);
		for(i=0;i<8000000;i++){}

			
	}
	
}
