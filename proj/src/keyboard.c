
#include "keyboard.h"


unsigned int khook_id = KB_IRQ;

unsigned long outbufass = 0;
unsigned long statusandobf= 0;


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
	khook_id = KB_IRQ;
	return 0;

}


unsigned long keyboard_int_handler() {

	unsigned long data;
		unsigned int n=0;
		unsigned long status;
		while( n<= 5)
		{
			sys_inb(STATUS_REG, &status);
			printf("ESTA A LER O TECLADO");
			if( status & OBF)
			{
				sys_inb(KBD_OUT_BUF, &data);

				if ( (status &(PAR_ERR | TO_ERR)) == 0 )
					return data;
				else
					return -1;
			}
			n++;

		}

		return -1;



}

int receive_buffer(unsigned long *out_buf, unsigned long *out_buf2)
{
	//(*out_buf) = keyboard_int_handler();
	do
	{
		keyboardasm();
	}while(statusandobf == 0);
	readoutbuf();
	(*out_buf) = outbufass;

	if((*out_buf) == -1)
		return 1;

	if((*out_buf) == OUT_BUF_2BYTES)
	{
		(*out_buf2) = (*out_buf)<<8;
		return 1 ;
	}

		(*out_buf) |= (*out_buf2);
		(*out_buf2) = 0;

	return 0;


}

int issue_cmd_kbd(unsigned long cmd)
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
    printf("Error trying to write in the input buffer\n");
    return -1;

}



void print_code(unsigned long *out_buf)
{

		if(*out_buf & BIT(7))
				{
					if((*out_buf) < 10)
					{
						printf("Break code: 0x0%X\n", *out_buf);
					}
					else
						printf("Break code: 0x%X\n", *out_buf);
				}
				else
				{
					if((*out_buf) < 10)
					{
						printf("Make code: 0x0%X\n", *out_buf);
					}
					else
						printf("Make code: 0x%X\n", *out_buf);
				}




}


void print_led(unsigned long leds_p, unsigned long flag)
{
	if(leds_p == 0)
	{
		if((flag & BIT(0)) != 0)
		{
			printf("Scroll lock is on\n");

		}
		else
		{
			printf("Scroll lock is off\n");

		}
	}
	else if(leds_p == 1)
	{
		if((flag & BIT(1)) != 0)
		{
			printf("Numeric lock is on\n");

		}
		else
		{
			printf("Numeric lock is off\n");

		}
	}
	else if(leds_p == 2)
	{
		if((flag & BIT(2)) != 0)
		{
			printf("Caps lock is on\n");

		}
		else
		{
			printf("Caps lock is off\n");

		}
	}
	else
	{
		printf("Not a valid led selected\n");

	}

}



int wait_esc()
{



}
