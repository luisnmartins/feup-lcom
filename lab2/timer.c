#include "i8254.h"
#include <minix/syslib.h>
#include <minix/drivers.h>



#define RBC_COUNT0 0xE2
#define RBC_COUNT1 0xE4
#define RBC_COUNT2 0xE8
#define COPY_4LAST 0x0F



int timer_set_square(unsigned long timer, unsigned long freq) {

		unsigned char conf;
		unsigned char final;
		timer_get_conf(timer, &conf);
		unsigned long div;
		div = TIMER_FREQ/freq;
		final = conf & COPY_4LAST;
		if (timer == TIMER_0)
		{
			final = final & 0x3f;
		}
		sys_outb(TIMER_CTRL, final);
		sys_outb(TIMER_0, )

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	if(timer == 0)
	{
		sys_outb(TIMER_CTRL, RBC_COUNT0);
		sys_inb(TIMER_0, st);
	}
	if(timer == 1)
	{
			sys_outb(TIMER_CTRL, RBC_COUNT1);
			sys_inb(TIMER_1, st);
	}
	if(timer == 2)
	{
			sys_outb(TIMER_CTRL, RBC_COUNT2);
			sys_inb(TIMER_2, st);
	}
	return 1;
}

int timer_display_conf(unsigned char conf) {

	int bcd=0, null=0, output=0;


	if(conf & BIT(0) == 1)
	{
		bcd = 1;
	}
	if(conf & BIT(6) == 1)
	{
		null = 1;
	}
	if(conf & BIT(7) == 1)
	{
		output = 1;
	}
	printf("BCD = %d\n", bcd);
	printf("Null Count = %d\n", null);
	printf("Output = %d\n", output);
	if(conf & BIT(3) == 0)
	{
		if(conf & BIT(2) == 0)
		{
			if(conf & BIT(1) == 0)
			{
				printf("Programmed Mode = INTERRUPT ON TERMINAL COUNT\n");

			}
			else if(conf & BIT(1) == 1)
			{
				printf("Programmed Mode = HARDWARE RETRIGGERABLE ONE-SHOT\n");

			}
		}
		else if(conf & BIT(2) == 1)
		{
			if(conf & BIT(1) == 0)
			{
				printf("Programmed Mode = RATE GENERATOR\n");

			}
			else if(conf & BIT(1) == 1)
			{
				printf("Programmed Mode = SQUARE WAVE MODE\n");

			}
		}
	}
	else if (conf & BIT(3) == 1)
	{
		if(conf & BIT(2) == 0)
		{
			if(conf & BIT(1) == 0)
			{
				printf("Programmed Mode = SOFTWARE TRIGGERED STROBE\n");

			}
			else if(conf & BIT(1) == 1)
			{
				printf("Programmed Mode = HARDWARE TRIGGERED STROBE (RETRIGGERABLE)\n");

			}
		}
		else if(conf & BIT(2) == 1)
		{
			if(conf & BIT(1) == 0)
			{
				printf("Programmed Mode = RATE GENERATOR\n");
			}
			else if(conf & BIT(1) == 1)
			{
				printf("Programmed Mode = SQUARE WAVE MODE\n");
			}
		}
	}
	if((conf & BIT(5) == 0) && (conf & BIT(4) == 1))
	{
		printf("Type of Access = LSB\n");
	}
	else if(conf & BIT(5) == 1)
	{
		if(conf & BIT(4) == 0)
		{
			printf("Type of Access = MSB\n");
		}
		else if (conf & BIT(4) == 1)
		{
			printf("Type of Access = LSB followed by MSB\n");
		}
	}


	return 1;
}

int timer_test_square(unsigned long freq) {

	timer_set_square(TIMER_0, freq);

	return 1;
}

int timer_test_int(unsigned long time) {

	return 1;
}

int timer_test_config(unsigned long timer) {

	unsigned char var;
	timer_get_conf(timer, &var);
	timer_display_conf(var);
	return 1;
}
