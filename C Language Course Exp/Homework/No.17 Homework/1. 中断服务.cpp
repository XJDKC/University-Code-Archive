#include<stdio.h>
#include<stdlib.h>
typedef struct isr_bits
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
}ISR_BITS;
union ISR_REG
{
    unsigned short all;	
    ISR_BITS bit;
}isr_reg;
void isr0(void);
void isr1(void);
void isr2(void);
void isr3(void);
void isr4(void);
void isr5(void);
void isr6(void);
void isr7(void);
int main()
{
	int n,i;
	unsigned short m;
	void (*p_isr[8])(void)={isr0,isr1,isr2,isr3,isr4,isr5,isr6,isr7};
	scanf("%d",&n);
	while (n--)
	{
		scanf("%hu",&isr_reg.all); 
		printf("%hu:\n",isr_reg.all);
		if (isr_reg.bit.bit0)   
		p_isr[0]();
		if (isr_reg.bit.bit1)   
		p_isr[1]();
		if (isr_reg.bit.bit2)   
		p_isr[2]();
		if (isr_reg.bit.bit3)   
		p_isr[3]();
		if (isr_reg.bit.bit4)   
		p_isr[4]();
		if (isr_reg.bit.bit5)   
		p_isr[5]();
		if (isr_reg.bit.bit6)   
		p_isr[6]();
		if (isr_reg.bit.bit7)   
		p_isr[7]();
		printf("\n");
	}
	return 0;
}
void isr0(void)
{
	 printf("The Interrupt Service Routine isr0 is called!\n");
}
void isr1(void)
{
	 printf("The Interrupt Service Routine isr1 is called!\n");
}
void isr2(void)
{
	 printf("The Interrupt Service Routine isr2 is called!\n");
}
void isr3(void)
{
	 printf("The Interrupt Service Routine isr3 is called!\n");
}
void isr4(void)
{
	 printf("The Interrupt Service Routine isr4 is called!\n");
}
void isr5(void)
{
	 printf("The Interrupt Service Routine isr5 is called!\n");
}
void isr6(void)
{
	 printf("The Interrupt Service Routine isr6 is called!\n");
}
void isr7(void)
{
	 printf("The Interrupt Service Routine isr7 is called!\n");
}

