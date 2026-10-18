
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

unsigned char memArr[16];

int main(void)
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0X00;
	DDRB=0x00;
	DDRC=0xFF;
	DDRD=0x00;
	
	int currclk = 0;
	int prevclk = 0;
	
	int memread;
	int memwrite;
	int writedata;
	int addr;
	int dataout;
	
	for(int i=0; i<16; i++){
		memArr[i]=13;
	}
	
	while (1)
	{
		int b = PINA;
		writedata = b>>4;
		addr = b%16;
		int d = PIND;
		prevclk = currclk;
		currclk = (d & 0b00000100)>>2;
		//mem2reg = (d & 0b0010)>>1;
		memread = (d & 0b00000010)>>1;
		memwrite = (d &0b00000001);
		
		dataout = memArr[addr];
		
		if(memread==1){
			PORTC = dataout;
		}
		if(prevclk==0 && currclk==1 && memwrite==1){
			memArr[addr] = writedata;
		}
		_delay_ms(10);
		
		
	}
}

//DataMemoryUpdated