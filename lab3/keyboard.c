#include "i8042.h"


int keyboard_subscribe_int() {

	if (sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&hook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(KB_IRQ);

}

int keyboard_unsubscribe_int() {

	if (sys_irqdisable(&hook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&hook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}

	return 0;

}


int keyboard_test_int(unsigned int &acabou) {
	unsigned long status;
	unsigned long out_buf, out_buf2;
	unsigned int 2bytes;
	sys_inb(STATUS_REG, &status);

	if(!(status & BIT(0)))
	{
		sys_inb(KBD_OUT_BUF, &out_buf);
		if(out_buf == ESC_CODE)
		{

				acabou = 1;
				return 0;
		}
		else
		{
			if(2bytes == 0)
			{
				out_buf2 = print_code(2bytes, out_buf);
			}
			else if(2bytes == 1)
			{
				out_buf |= out_buf2;
				print_code(2bytes, out_buf);
			}

		}
									if(out_buf == OUT_BUF_2BYTES)
									{
										out_buf<<8;
										sys_inb(STATUS_REG, &status);
										if(!(status & BIT(0)))
										{
											sys_inb(KBD_OUT_BUF, &out_buf2);
											out_buf |= out_buf2;
										}

									}



void read(unsigned char port, unsigned long &var)
{


}

unsigned long print_code(unsigned int &2bytes,unsigned long &out_buf)
{
	if((out_buf == OUT_BUF_2BYTES) && (2bytes == 0))
	{
		2bytes = 1;
		return out_buf<<8;
	}
	else if(2bytes == 1)
	{

		if(out_buf & BIT(15))
		{
			printf("Break code: %x\n", out_buf);
		}
		else
		{
			printf("Make code: %x\n", out_buf);
		}
		2bytes = 0;
	}
	else if(2bytes == 0)
	{
		if(out_buf & BIT(7))
		{
			printf("Break code: %x\n", out_buf);
		}
		else
		{
			printf("Make code: %x\n", out_buf);
		}

	}


}
