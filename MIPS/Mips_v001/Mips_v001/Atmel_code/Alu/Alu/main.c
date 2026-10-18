 
 #define F_CPU 1000000
 #include <util/delay.h>
 #include <avr/io.h>
 // generated based on our provided serial
 // like 1 is sw and .....



 unsigned char memArr[32];

 int main(void)
 {
	 MCUCSR|=(1<<JTD);
	 MCUCSR|=(1<<JTD);
	 
	 
	 DDRA=0X00;
	 DDRB=0x00;
	 DDRC=0xFF;
	 DDRD=0x00;

	 //DDRA=0X00; // ShowAddr A0 to A4; A5-> showaddrflag
	 
	 // reg1 BL
	 // reg2 DL
	 // opc BH
	 // out CL
	 // zero A0


	 //  PORTA = 0b00000001;
	 //  PORTB = 0b11111111;
	 //  PORTD = 0b00001111;
	 //  PORTC = 0b00001111;

	 int reg1=0x00;
	 int reg2=0x00;
	 int operation=0x00;
	 int dataOutputReg = 0x00;
	 int zeroFlag = 0;
	 

	 while (1)
	 {
		 operation = PIND&0b00000111;
		 
		 reg1 = PINA%16;
		 reg2 =  (PINA >> 4);
		 
		 
		 if(operation==0){
			 dataOutputReg = reg1 & reg2;
		 }else if (operation==1)
		 {
			 dataOutputReg = reg1 | reg2;
			 }else if(operation==2){
			 dataOutputReg = (reg1 + reg2)%16;
			 }else if(operation==3){
			 dataOutputReg = (reg1 - reg2 +16 )%16;
			 }else if(operation==4){
			 dataOutputReg = reg1 | reg2;
			 dataOutputReg = (dataOutputReg ^ 15);
			 }else if(operation==5){
			 if(reg1<reg2){
				 dataOutputReg=15;
			 }
			 }else if(operation==6){
			 dataOutputReg = reg1 << reg2;
			 dataOutputReg%=16;
			 }else if(operation==7){
			 dataOutputReg = reg1 >> reg2;
		 }
		 
		 //  if (operation == add || operation ==addi || operation == lw || operation == sw)
		 //  {
		 // 	 dataOutputReg = (reg1 + reg2)%16;
		 //  }
		 //  else if (operation == sub || operation == subi || operation == beq || operation == bneq)
		 //  {
		 // 	 dataOutputReg = (reg1 - reg2 +16 )%16;
		 
		 //  }
		 //  else if (operation == and || operation == andi)
		 //  {
		 // 	 dataOutputReg = reg1 & reg2;
		 //  }
		 //  else if (operation == or || operation == ori)
		 //  {
		 // 	 dataOutputReg = reg1 | reg2;
		 //  }
		 //  else if (operation == nor)
		 //  {
		 // 	 dataOutputReg = reg1 | reg2;
		 // 	 dataOutputReg = (dataOutputReg ^ 15);
		 //  }
		 //  else if (operation == sll)
		 //  {
		 // 	 dataOutputReg = reg1 << reg2;
		 // 	 dataOutputReg%=16;
		 //  }
		 //  else if (operation == srl)
		 //  {
		 // 	 dataOutputReg = reg1 >> reg2;
		 //  }
		 //  else if (operation == j)
		 //  {
		 // 	 dataOutputReg = 0;
		 //  }

		 if (dataOutputReg%16 == 0)
		 {
			 zeroFlag = 1;
		 }
		 else
		 {
			 zeroFlag = 0;
		 }
		 
		 //bsel = (zeroFlag&beqf)|((!zeroFlag)&bneqf);
		 
		 /*PORTC = 0x00;*/
		 unsigned char f = dataOutputReg | (zeroFlag<<4);
		 PORTC = f;
		 
		 
		 
		 _delay_ms(10);
	 }
 }
 //Arithmetic and Logic Unit