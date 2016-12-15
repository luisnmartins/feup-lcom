
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
static int flag_colision = 0;

//TODO if(2p 2 snakes) {aloca memoria snake 2 cobra}

void check_game_status(states *st, event *ev)
{


	switch(*st){
	case MENU_T:
		{

			if(*ev == OPTA)
			{
				printf("fixe\n");
				Snake *s2 = (Snake*)(malloc(sizeof(Snake)));
				s1 = s2;
				new_snake(5,10,32, s1);

				//printf("COL: %d\n", s1->head->col);
				//printf("ROW: %d\n", s1->head->row);
				if(s1->tail == NULL || s1->head == NULL)
					printf("nao deu\n");
				*ev = START_E;
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
			printf("tenta mudar de estado\n");
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
	return;

}

void keyboard_event_handler(unsigned long out_buf)
{
	printf("P: %d", p);
	if(p == END_T)
	{
		if(out_buf == ESC_CODE)
			vg_exit();
	}
	if(out_buf == ESC_CODE)
	{
		s1->head->orientation = RIGHT_DOWN;
		s1->head->direction = VERTICAL;
	}
	if(out_buf & 0xFF00 == 0xE0)
	{

	}
}

void change_to_start()
{
	event col_event2 = OPTA;
	check_game_status(&p, &col_event2);
	//printf("COL1: %d\n", s1->head->col);
	//printf("ROW1: %d\n", s1->head->row);
}


void timer_event_handler(unsigned short counter)
{

	if(p == MENU_T)
	{
		change_to_start();
		printf("changed\n");
	}

	if(flag_colision == 1)
				{

					printf("mudanca estado\n");
					printf("%d\n", p);
					event col_event = COLISION;
					check_game_status(&p, &col_event);
					draw_screen();
					printf("p: %d\n",p);


				}

	if(counter%30 == 0)
	{
		printf("procesing\n");
		//printf("R: %d\n", s1->head->row);
		//printf("C: %d\n", s1->head->col);


		if(p == SP_T)
		{

			move_snake(s1);
			printf("running\n");
			flag_colision = update_matrix_snake(s1);
			printf("Flag colision: %d\n", flag_colision);
			printf("matrix updated\n");
			draw_screen();
			//memcpy(video_mem, double_buffer, SCREEN_SIZE);



		}
	}
	return;
}
