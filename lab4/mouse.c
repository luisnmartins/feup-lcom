#include "mouse.h"

unsigned int mhook_id = MS_IRQ;

int mouse_subscribe_int()
{

	if (sys_irqsetpolicy(MS_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mhook_id) != OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&mhook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(MS_IRQ);
}

int mouse_unsubscribe_int() {

	if (sys_irqdisable(&mhook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&mhook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}

	return 0;

}


unsigned long mouse_int_handler() {

	unsigned long data;
		unsigned int n=0;
		unsigned long status;
		while( n<= 5)
		{
			sys_inb(STATUS_REG, &status);
			if((status & OBF) & AUX)
			{
				sys_inb(MS_OUT_BUF, &data);

				if ( (status &(PAR_ERR | TO_ERR)) == 0 )
					return data;
				else
					return 1;
			}
			tickdelay(micros_to_ticks(DELAY_US));
			n++;

		}

		return 1;


}


int issue_cmd_ms(unsigned long cmd)
{

	unsigned long stat=0;
	unsigned int n=0;
    while( n<= 5 )
    {

        sys_inb(STATUS_REG, &stat); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
        if( (stat & IBF) == 0 )
        {
        	sys_outb(MS_OUT_BUF, cmd);
        	//sys_outb(KBC_CMD_REG, cmd); /* no args command */
            return 0;
        }

        tickdelay(micros_to_ticks(DELAY_US));
        n++;
    }
    printf("Error trying to write in the input buffer\n");
    return -1;

}

void print_packet(int size_array, unsigned long *array)
{
	int i=0;
	int flag=0;
	unsigned long byte1=array[0];
	for(i; i<size_array; i++)
	{
		printf("B%d=%x", size_array, array[i]);
		printf("    ");

	}
	int n=0;
	for(n; n<3; n++)
	{
		if(byte1 & BIT(n))
			flag=1;
		else
			flag=0;
		if(n == 0)
		{
			printf("LB=%x     ", flag);
		}
		else if(n == 1)
		{
			printf("MB=%x     ", flag);
		}
		else if(n == 2)
		{
			printf("RB=%x     ", flag);
		}

	}
	byte1>>6;
	flag=0;
	if(byte1 & BIT(0))
	{
		flag=1;


	}
	printf("XOV=%x     ", flag);
	flag=0;
	if(byte1 & BIT(1))
	{
		flag=1;

	}
	printf("YOV=%x\n", flag);


}
