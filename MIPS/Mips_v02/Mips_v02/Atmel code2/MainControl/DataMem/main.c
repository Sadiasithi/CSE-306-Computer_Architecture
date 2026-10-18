
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

unsigned char memArr[16];

int main(void)
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0X00;
	DDRB=0xFF;
	DDRC=0x00;
	DDRD=0xFF;
	
	int currclk = 0;
	int prevclk = 0;
	
	int memread;
	int memwrite;
	int writedata;
	int mem2reg;
	int addr;
	int dataout;
	
	for(int i=0; i<16; i++){
		memArr[i]=13;
	}
	
	while (1)
	{
		int a = PINA;
		//writedata = b>>4;
		addr = a%16;
		int c = PINC;
		writedata = c & 0b00001111;
		prevclk = currclk;
		currclk = (a & 0b10000000)>>7;
		memwrite = (a>>4) & 0b0001;
		memread = ((a>>4) & 0b0010)>>1;
		mem2reg = ((a>>4) & 0b0100)>>2;
		if(mem2reg==1){
			if(memread==1)dataout=memArr[addr];
			else dataout=0x00;
		}else{
			dataout=addr;
		}
		//dataout = memArr[addr];
		
		//if(memread==1){
		PORTB = dataout;
		
		if(prevclk==0 && currclk==1 && memwrite==1){
			memArr[addr] = writedata;
		}
		_delay_ms(10);
		
		
	}
}

//DataMemoryUpdated