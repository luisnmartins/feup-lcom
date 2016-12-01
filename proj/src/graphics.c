
#include "graphics.h"


int paint_snake_hor(unsigned int x, unsigned int y, unsigned int size, unsigned int right)
{
	int i=0;
	int ultimo_pintado;

	if(right == 1)
	{
		for(i;i<size; i++)
		{

			if(x< 0 || y<0 || x>1023 || y>767)
				return 1;
			paint_xpm(x, y, square_right);
			x += 19;
		}
		return x-19;
	}
	else
	{
		//paint_xpm(200, 150, square_right);
		for(i;i<size; i++)
		{
				if(x<0 || y<0 || x>1023 || y>767)
					return 1;
				paint_xpm(x, y, square_left);
				x-=19;
		}
		return x+19;
	}



}

int move_snake(unsigned int x, unsigned int y, unsigned short hor,unsigned int xant)
{

		int ipc_status;
		int irq_set2 = keyboard_subscribe_int();
		int irq_set = timer_subscribe_int();

		message msg;
		int r;
		int i, a;
		unsigned short yant=200;
		unsigned long out_buf = 0;
		unsigned long out_buf2=0;
		out_buf = keyboard_int_handler();
		out_buf =0;
		int flag =0;

		int contador=0;

		while (out_buf!= 0xE0C8 && out_buf!= 0xE0D0) {

				if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
				}
				if (is_ipc_notify(ipc_status)) { /* received notification */
					switch (_ENDPOINT_P(msg.m_source)) {
					case HARDWARE: /* hardware interrupt notification */
						if(msg.NOTIFY_ARG & irq_set2)
						{
							out_buf = keyboard_int_handler();
							if(out_buf == 0xE0)
							{
								out_buf2 = out_buf<<8;
								flag =1;
								continue;
							}
							if(flag == 1)
							{
								out_buf |= out_buf2;
								out_buf2 = 0;
								continue;
							}

						}

					if (msg.NOTIFY_ARG & irq_set) {

						out_buf =0;
		 				if(contador%30 == 0)
						{
							if (hor == 0)
									y += 19;
							else
									x += 19;

								paint_black_xpm(xant, yant, square_right);

								if(paint_xpm(x, y, square_right) == 1)
									break;
								else
								{
									xant = xant+19;

								}
							}
						contador++;
					}
						}
					}
				}


		if (timer_unsubscribe_int() != 0) {

			return 1;
		}
		if(keyboard_unsubscribe_int() != 0)
		{
			return 1;
		}
		out_buf = keyboard_int_handler();

		return 0;
}


