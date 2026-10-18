#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>


int main(void)
{
	DDRA=0X00;
	DDRB=0x00;
	DDRC=0xFF;
	DDRD=0xFF;
	
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	unsigned char pc;
	int prevclk = 0;
	int currclk = 0;
	int reset = 0;
	
	/* Replace with your application code */
	while (1) {
		prevclk = currclk;
		//char b = PINA;
		char x= PINB;
		currclk = ( x & 0b00010000)>>4;
		reset = ( x & 0b00001000)>>3;
		
		
		if(reset==1){
			PORTD = 0x00;
		}
		else{
			if(prevclk ==1 && currclk ==0){
				pc = PINA;
				PORTD = pc;
			}
		}
	}
}
//PC Register