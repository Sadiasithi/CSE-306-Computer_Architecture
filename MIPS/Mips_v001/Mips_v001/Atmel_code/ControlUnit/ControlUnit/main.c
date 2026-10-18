
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>

// generated based on our provided serial
// like 1 is sw and .....




// defining our operations for producing ALUOP and selectors for each and every mux . ALUOP is not needed actually . This part is done in our circuit

unsigned char memArr[32];
int controlMem[16] = {0x902,0x904,
	0x001,0x036,
	0x444,0x026,
	0x506,0x784,
	0x50e,0x908,
	0x502,0x906,
	0x500,0x900,
0x50c,0x504};

int main(void)
{
	// To use PC2,3,4,5 pins for general I/O operations, JTAG must be disabled.(Enable JTD twice)
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	
	
	DDRA=0xFF;
	DDRB=0X00;
	DDRD=0X00;
	DDRC=0XFF;

	//DDRA=0X00; // ShowAddr A0 to A4; A5-> showaddrflag
	
	// opc BL
	// mRrWrDj AL
	// bNbEm2RmW AH
	// aluOPaluSRC CL


	// PORTA = 0b11111111; // assign it as output
	// PORTB = 0b00000000; // will take input for register1 and shift operation
	// PORTD = 0b00000000; // takes input for register 2
	// PORTC = 0b00001111; // shows output in the LSB part



	while (1)
	{
		unsigned int operation = PINB & 0b00001111;
		// taking input such as ADD OR , based on 4 bits
		// actually 0-15
		unsigned char tmp = (controlMem[operation] & 0b00001110)>>1;//got ALU op
		tmp=tmp|((controlMem[operation] & 0x01)<<3);
		tmp=tmp | (controlMem[operation] & 0b11110000);
		//int ctrlOUT1 = controlMem[operation]%256;
		// now we have the value for each mux and aluop in int form
		
		PORTA = tmp & 0b11111111;
		// getting complete last 8 bit address in portA

		//ctrlOUT1 = controlMem[operation]/256;
		tmp=(controlMem[operation]>>8) & 0b00001111;
		
		//PORTC = (ctrlOUT1 & 0b00001111)|( (operation<<4) & 0b11110000);
		//this will have the remaining 4 bits
		PORTC=tmp;
		// combining PORTA and PORTC = mux selectors + ALUOP

		_delay_ms(10);
	}
}
//Control