#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>




int main(void)
{
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	
	DDRA=0X00;
	DDRB=0x00;
	DDRC=0xFF;
	DDRD=0x00;
	
	
	
	
	
	while (1)
	{
		int beq=0;
		int jmp=0;
		
		int a= PINA;
		int b = PINB;
		jmp= (b & 0b00100000)>>5;
		beq=(b & 0b01000000)>>6;
		int shmt=0;
		shmt=(b & 0x0f);

		int jmp_addr=0;
		jmp_addr=PIND;
		int pc=a+1;
		if(jmp==1){
			PORTC=jmp_addr & 0xff;
			}else if(beq==1){
			pc=pc+shmt;
			PORTC=pc & 0xff;

			}else{
			PORTC=pc & 0xff;
		}
		// int muxout = b%16;
		// int pnA=PINA;
		// int reg2 = pnA>>4;
		// // int d = PIND;
		// int reg1 = pnA%16;
		// int flg = PIND;
		// prevclk = currclk;
		// currclk = (flg & 0b00000010)>>1;
		// regwrite = (flg & 0b00000001);
		// //showreg = (flg & 0b0100)>>2;
		// showreg=0;
		// //reset = (flg & 0b1000)>>3;
		// reset=0;
		// int wb = b>>4;
		
		// if(showreg==1){
		// 	int in1 = PIND>>4;
		// 	PORTC = regArr[in1];
		// }
		// else{
		// 	if(reset==1){
		// 		for(int i=0; i<16; i++){
		// 			regArr[i]=0;
		// 		}
		// 	}
		// 	else{
		// 		PORTC = ( (regArr[reg2]<< 4) | regArr[reg1]%16)%256;
		// 		if(prevclk==0 && currclk == 1 && regwrite){
		// 			regArr[muxout] = wb;
		// 		}
		// 	}
		// }
		_delay_ms(10);
	}
}
//Register File