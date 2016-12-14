
#include "man_events.h"


typedef enum {
	MENU_T, SP_T, MP_T, MOKB_T ,KBC_T, EXIT_T, END_T
} states;

typedef enum {
	OPTA, OPTB, OPTC, COLISION, START_E //mais cenas
} event;

states p=MENU_T;

//static states *matrix_states[64][64] = {NULL};   //col x line

static Snake *s1;

//TODO if(2p 2 snakes) {aloca memoria snake 2 cobra}

void check_game_status(states *st, event *ev)

{

	switch(*st){
	case MENU_T:
		{

			if(*ev == OPTA)
			{
				printf("fixe\n");
				s1 = new_snake(5,10,32);

				*st = SP_T;
			}
			else if (*ev == OPTB)
				*st = MP_T;
			else if (*ev == OPTC)
				*st = EXIT_T;
			break;
		}
	/*case EXIT:
		//sai do programa
		break;*/
	case SP_T:
		//TODO
	{
		if(*ev == COLISION)
		{
			*st = END_T;
		}
		break;
	}
	case MP_T:
		if(*ev == OPTA)
		{
			//TODO gera ecra e cobra
			*st = KBC_T;
		}
		else if (*ev == OPTB)
		{
			//TODO gera ecra e cobra
			*st = MOKB_T;
		}
		break;

	}

}

void keyboard_event_handler(unsigned long out_buf)
{

	if(p == END_T)
	{
		if(out_buf == ESC_CODE)
			vg_exit();
	}
	if(out_buf & 0xFF00 == 0xE0)
	{

	}
}

void timer_event_handler(unsigned short counter)
{
	int flag_colision = 0;
	event col_event2 = OPTA;
	check_game_status(&p, &col_event2);
	if(counter%30 == 0)
	{


		if(p == SP_T)
		{

			move_snake(&s1);

			flag_colision = update_matrix_snake(&s1);
			draw_screen();
			//memcpy(video_mem, double_buffer, SCREEN_SIZE);
			if(flag_colision == 1)
			{
				event *col_event = COLISION;
				check_game_status(&p, col_event);
			}


		}
	}

}
