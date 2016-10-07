#include <minix/syslib.h>
#include <minix/drivers.h>

#define RBC_COUNT0 0x11100010
#define RBC_COUNT1 0x11100100
#define RBC_COUNT2 0x11101000

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned char conf;
	if(timer == 0)
	{
		sys_inb(TIMER_0, &conf);
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
		sys_outb(TIMER_CRTL, RBC_COUNT0);
		sys_inb(TIMER_0, st);
	}
	if(timer == 1)
	{
			sys_outb(TIMER_CRTL, RBC_COUNT1);
			sys_inb(TIMER_1, st);
	}
	if(timer == 2)
	{
			sys_outb(TIMER_CRTL, RBC_COUNT2);
			sys_inb(TIMER_2, st);
	}
	return 1;
}

int timer_display_conf(unsigned char conf) {
	
	int bcd=0, null=0, output=0;
	string mode;
	string type_access;

	if(conf & BIT(0) == 1)
	{
		bcd = 1;
	}
	if(conf & BIT(3) == 0)
	{
		if(conf & BIT(2) == 0)
		{
			if(conf & BIT(1) == 0)
			{
				mode = "INTERRUPT ON TERMINAL COUNT";
			}
			else if(conf & BIT(1) == 1)
			{
				mode = "HARDWARE RETRIGGERABLE ONE-SHOT";
			}
		}
		else if(conf & BIT(2) == 1)
		{
			if(conf & BIT(1) == 0)
			{
				mode = "RATE GENERATOR";
			}
			else if(conf & BIT(1) == 1)
			{
				mode = "SQUARE WAVE MODE";
			}
		}
	}
	else if (conf & BIT(3) == 1)
	{
		if(conf & BIT(2) == 0)
		{
			if(conf & BIT(1) == 0)
			{
				mode = "SOFTWARE TRIGGERED STROBE";
			}
			else if(conf & BIT(1) == 1)
			{
				mode = "HARDWARE TRIGGERED STROBE (RETRIGGERABLE)";
			}
		}
		else if(conf & BIT(2) == 1)
		{
			if(conf & BIT(1) == 0)
			{
				mode = "RATE GENERATOR";
			}
			else if(conf E BIT(1) == 1)
			{
				mode = "SQUARE WAVE MODE";
			}
		}
	}
	if((conf & BIT(5) == 0) && (conf & BIT(4) == 1))
	{
		type_access = "LSB";
	}
	else if(conf & BIT(5) == 1)
	{
		if(conf & BIT(4) == 0)
		{
			type_access = "MSB";
		}
		else if (conf & BIT(4) == 1)
		{
			type_access = "LSB followed by MSB";
		}
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
	printf("Programmed Mode = %s\n", mode);
	printf("Type of Access = %s\n", type_access);

	return 1;
}

int timer_test_square(unsigned long freq) {
	


	return 1;
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	
	unsigned char var;
	timer_get_conf(timer, &var)
	timer_display_conf(var);
	return 1;
}
