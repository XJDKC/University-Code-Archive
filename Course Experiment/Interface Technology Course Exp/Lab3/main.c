/*
 * main.c for microAptiv_UP MIPS core running on Nexys4DDR
 * Prints \n\rMIPSfpga\n\r out via UART.
 * Default baudrate 115200,8n1.
 * Also display a shifting 0xf on the LEDs
 */

#include "fpga.h"

#define inline_assembly()  asm("ori $0, $0, 0x1234")

#define CLK_FREQ 50000000
#define SEGM_BASE 0x10E00000

#define UART_BASE 0xB0401000	//With 1000 offset that axi_uart16550 has
#define rbr		0*4
#define ier		1*4
#define fcr		2*4
#define lcr		3*4
#define mcr		4*4
#define lsr		5*4
#define msr		6*4
#define scr		7*4

#define thr		rbr
#define iir		fcr
#define dll		rbr
#define dlm		ier

#define PWM_BASE 0xB0C00000

void delay();
void uart_outbyte(char c);
char uart_inbyte(void);
void uart_print(const char *ptr);

//------------------
// main()
//------------------
int main() {
	volatile unsigned int pushbutton, count = 0xF;
	volatile unsigned int j = 1,i;
	unsigned int value = 0;
	unsigned int num = 0;

	*WRITE_IO(UART_BASE + lcr) = 0x00000080; // LCR[7]  is 1
	delay();
	*WRITE_IO(UART_BASE + dll) = 27; // DLL msb. 115200 at 50MHz. Formula is Clk/16/baudrate. From axi_uart manual.
	delay();
	*WRITE_IO(UART_BASE + dlm) = 0x00000000; // DLL lsb.
	delay();
	*WRITE_IO(UART_BASE + lcr) = 0x00000003; // LCR register. 8n1 parity disabled
	delay();
	*WRITE_IO(UART_BASE + ier) = 0x00000000; // IER register. disable interrupts
	delay();
		
	//*WRITE_IO(UART_BASE + ier) = 0x00000001; // IER register. Enables Receiver Line Status and Received Data Interrupts
	//delay();

	while(1) {
		num = 0;

		inline_assembly();	  	
		// End of LEDs display


		// PWM IP test
		/* Prompt the user to select a brightness value ranging from  0 to 9. */
		for (i = 0; i < 8; i++)
		{
			uart_print("Select a Brightness between 0 and F\n\r");

        	/* Read an input value from the console. */
        	value = uart_inbyte();

			*WRITE_IO(UART_BASE + thr) = value;

	        /* Convert the input ASCII character to an integer value. */
	        if (value >= '0' && value <= '9') 
	        	value = value - '0'; 
	       	else 
	       		value = value - 'A' + 10;

	        num = num * 16 + value;

	        /* Print the input value back to the console to provide some feedback to the user. */
			
			delay( );
	        uart_print("\n\r");
			
			// End of PWM IP test		
		}

		uart_print("Press any button to start\n\r");
		while(!((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001))
		{	
			*WRITE_IO(SEGM_BASE) = num;
			num = num << 4 | (( (num & 0xf0000000) >> 28) & 0x0000000f);
			delay();
		}
		value = *READ_IO(UART_BASE + rbr);
		*WRITE_IO(UART_BASE + thr) = value;
	}
	
	return 0;
}

void delay() {
	volatile unsigned int j;

	for (j = 0; j < (10000); j++) ;	// delay 
}

void uart_outbyte(char c) {
	*WRITE_IO(UART_BASE + thr) = (unsigned int) c;
	delay( );
}

char uart_inbyte(void) {
	unsigned int RecievedByte;
	
	while(!((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001));
	RecievedByte = *READ_IO(UART_BASE + rbr);

	return (char)RecievedByte;
}

void uart_print(const char *ptr)
{
	while (*ptr) {
		uart_outbyte (*ptr);
		ptr++;
	}
}

