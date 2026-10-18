#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

unsigned char regArr[16];
//0 -> zero lol
//1 -> t0
//2 -> t1
//3 -> t2
//4 -> t3
//5 -> t4
//6 -> sp



int main(void)
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0X00;
	DDRB=0x00;
	DDRC=0xFF;
	DDRD=0x00;
	
	for(int i=1; i<16; i++){
		regArr[i]=i;
	}
	regArr[0]=0;
	regArr[6]=15;
	
	int currclk=0;
	int regwrite;
	int showreg;
	int reset;
	int prevclk=0;
	
	while (1)
	{
		int b = PINB;
		int muxout = b%16;
		int pnA=PINA;
		int reg2 = pnA>>4;
		// int d = PIND;
		int reg1 = pnA%16;
		int flg = PIND;
		prevclk = currclk;
		currclk = (flg & 0b00000010)>>1;
		regwrite = (flg & 0b00000001);
		showreg = (flg & 0b00000100)>>2;
		//showreg=0;
		//reset = (flg & 0b1000)>>3;
		reset=0;
		int wb = b>>4;
		
		if(showreg==1){
			int in1 = PIND>>4;
			PORTC = regArr[in1] ;
		}
		else{
			if(reset==1){
				for(int i=0; i<16; i++){
					regArr[i]=0;
				}
			}
			else{
				PORTC = ( (regArr[reg2]<< 4) | regArr[reg1]%16)%256;
				if(prevclk==0 && currclk == 1 && regwrite){
					regArr[muxout] = wb;
				}
			}
		}
		_delay_ms(10);
	}
}
//Register File