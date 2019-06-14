/*
 * main.c for microAptiv_UP MIPS core running on Nexys4DDR
 * Prints \n\rMIPSfpga\n\r out via UART.
 * Default baudrate 115200,8n1.
 * Also display a shifting 0xf on the LEDs
 */

#include "fpga.h"

#define inline_assembly()  asm("ori $0, $0, 0x1234")

#define CLK_FREQ 50000000



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
#define SEGM_BASE 0xB1A00000

#define IS_UART_INTR (1<<15)
#define IS_PWM_INTR (1<<14)
#define IS_TIMER_INTR (1<<30)


void Rev_Pwm();
void Rev_Led();
void Display_Switch();
void delay();
void uart_outbyte(char c);
char uart_inbyte(void);
void uart_print(const char *ptr);
extern char *reverse(char *s);
extern char *my_itoa(int n);


extern void delay_ms(unsigned int ms_count);

// The following is for ADT7420
#include "i2c.h"
#include "ADT7420.h"

/*****************************************************************************/
/********************** Variable Definitions *********************************/
/*****************************************************************************/
volatile unsigned int rxData = 0;

char s[10] = "";
volatile unsigned int len = 0;

//------------------
// main()
//------------------
int main() {
	volatile unsigned int pushbutton, count = 0xF;
	volatile unsigned int j = 1;


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
		
	*WRITE_IO(UART_BASE + ier) = 0x00000001; // IER register. Enables Receiver Line Status and Received Data Interrupts
	delay();
	
	// Begin ADT7420 test
	// Initialize ADT7420 Device
	ADT7420_Init();

	*WRITE_IO(SEGM_BASE) = 0;
	// Display Main Menu on UART
	//ADT7420_DisplayMainMenu();

	volatile int signal = 0;
	  Display_Temp(ADT7420_ReadTemp());	//send temp
		Display_Switch();					//send switch
	while(!signal)
    {

   		//Display_Temp(ADT7420_ReadTemp());	//send temp
		//Display_Switch();					//send switch
	
		rxData = uart_inbyte();	
		uart_print("receive\n");
		
		uart_print(my_itoa(rxData));
		uart_print("\n");


		if (rxData == 'L')
		{
			s[1] = uart_inbyte();
			uart_print("receive\n");
			uart_print(my_itoa(s[1]));
			Rev_Led();
			rxData = 0;
		}
		else if (rxData == 'P')
		{		
			s[1] = uart_inbyte();
			Rev_Pwm();
			*WRITE_IO(SEGM_BASE) = s[1] - 0x30;
			rxData =0;

		}
		else if (rxData == 'Q')
		{
			signal = 1;
		}
    }
			
	return 0;
}

void Rev_Pwm(){			//injput_data: 0~9
	//unsigned int RecievedByte;
	//RecievedByte = *READ_IO(UART_BASE + rbr);

	*WRITE_IO(PWM_BASE) = 110000 * (s[1] - 0x30);
	// RecievedByte = *READ_IO(UART_BASE + rbr);
}

void Rev_Led() {		//input_data: 0~9
	//unsigned int RecievedByte;
	volatile unsigned int lednum = 0xFFFF;
	// while((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001){  //'0~9''\n'
	//RecievedByte = *READ_IO(UART_BASE + rbr);
	
	// *WRITE_IO(IO_LEDR) = lednum >> (32- (s[1] - 0x30));
	
	volatile unsigned int zzx = 0;
	volatile unsigned int cjj = 1;
	volatile unsigned int i;
	for (i = 0; i < s[1] - 0x30; i++)
	{
		zzx = zzx | cjj;
		cjj = cjj * 2;
	}

	*WRITE_IO(IO_LEDR) = zzx;
	// *WRITE_IO(IO_LEDR) = s[1] - 0x30;
	
}


void Display_Switch(){
	unsigned int num = 0;
	num = (*READ_IO(IO_SWR)) & 0x3f;
	uart_print("S");
	uart_print(my_itoa(num));
	uart_print("\n");
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
	unsigned int count = 0;
	
	while(!((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001))
	{
		if (++count == 50) {
			Display_Temp(ADT7420_ReadTemp());	//send temp
			count = 0;
			//uart_print("t");

		}
		Display_Switch();					//send switch
	}

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
/*
if((*READ_IO(UART_BASE + lsr) & 0x00000001)==0x00000001)
	revdata = *READ_IO(UART_BASE + rbr);
*/


void _mips_handle_irq(void* ctx, int reason)
{
	if(reason & IS_TIMER_INTR) {
	// write C0_Compare = $11
		asm volatile ("mtc0	$0, $11");
			
		asm volatile ("li $9, 0x1");
		// write C0_COUNT = $9
		asm volatile ("mtc0 $9, $9");
		uart_print("TIMER interrupts occurred!\n\r");
		return;
	}
	/*
	else if(reason & IS_UART_INTR) {
		rxData = *READ_IO(UART_BASE + rbr);
		data_received = 0x1;
		uart_print("UART interrupts occurred!\n\r");
		return;
	}
	*/
	else if(reason & IS_PWM_INTR) {
		*WRITE_IO(PWM_BASE) = 0x0;
		uart_print("PWM interrupts occurred!\n\r");
		return;
	}

	
	else {
		uart_print("Other interrupts occurred!\n\r");
	}

}

