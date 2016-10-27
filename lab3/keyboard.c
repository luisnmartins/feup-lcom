#include "i8042.h"
#include "keyboard.h"


unsigned int khook_id = KB_IRQ;


int keyboard_subscribe_int() {

	if (sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &khook_id) != OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&khook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(KB_IRQ);

}

int keyboard_unsubscribe_int() {

	if (sys_irqdisable(&khook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&khook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}

	return 0;

}


int keyboard_test_int() {

	unsigned int data;
		unsigned int n=0;
		unsigned long status;
		while( n<= 5)
		{
			sys_inb(STATUS_REG, &status);
			if( status & OBF)
			{
				sys_inb(KBD_OUT_BUF, &data);

				if ( (status &(PAR_ERR | TO_ERR)) == 0 )
					return data;
				else
					return -1;
			}
			tickdelay(micros_to_ticks(DELAY_US));
			n++;

		}
		return -1;



}

unsigned int issue_cmd_kbd(unsigned long cmd)
{

	unsigned long stat=0;
	unsigned int n=0;
    while( n<= 5 )
    {

        sys_inb(STATUS_REG, &stat); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
        if( (stat & IBF) == 0 )
        {
        	sys_outb(KBD_OUT_BUF, cmd);
        	//sys_outb(KBC_CMD_REG, cmd); /* no args command */
            return 0;
        }

        tickdelay(micros_to_ticks(DELAY_US));
        n++;
    }
    return -1;

}



void print_code(unsigned long *out_buf)
{

		if(*out_buf & BIT(7))
				{
					printf("Break code: %X\n", *out_buf);
				}
				else
				{
					printf("Make code: %X\n", *out_buf);
				}




}


int print_led(int leds_p, int *flag)
{
	if(leds_p == 0)
	{
		if(*flag==0)
		{
			printf("Scroll lock is on\n");
			*flag=1;
		}
		else
		{
			printf("Scroll lock is off\n");
			*flag=0;
		}
	}
	else if(leds_p == 1)
	{
		if(*flag==0)
		{
			printf("Numeric lock is on\n");
			*flag=1;
		}
		else
		{
			printf("Numeric lock is off\n");
			*flag=0;
		}
	}
	else if(leds_p == 2)
	{
		if(*flag==0)
		{
			printf("Caps lock is on\n");
			*flag=1;
		}
		else
		{
			printf("Caps lock is off\n");
			*flag=0;
		}
	}
}
