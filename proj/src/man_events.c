
#include "man_events.h"

typedef enum {
	MENU_T, SP_T, MP_T, MOKB_T ,KBC_T, EXIT_T, END_T
} states;

typedef enum {
	OPTA, OPTB, OPTC, COLISION, START_E ,ESC_PRESSED//mais cenas
} event;

states p=MENU_T;


//static states *matrix_states[64][64] = {NULL};   //col x line

static Snake *s1;
static int flag_colision = 0;
static int buf_full =0;

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
				update_matrix_snake(s1);
				new_object_matrix(s1);
				draw_screen();
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

int keyboard_event_handler(unsigned long out_buf)
{
	printf("P: %d", p);
	if(p == END_T)
	{
		if(out_buf == ESC_CODE)
		{
			return 1;
		}
	}
	if(p == SP_T)
	{
		if(buf_full == 1)
			return 0;

		if(s1->head->direction == HORIZONTAL)
		{
			if(out_buf == UP_ARROW)
			{
				s1->head->direction = VERTICAL;
				s1->head->orientation = LEFT_UP;
				buf_full = 1;
			}
			else if(out_buf == DOWN_ARROW){
				s1->head->direction = VERTICAL;
				s1->head->orientation = RIGHT_DOWN;
				buf_full = 1;
			}
		}
		else
		{
			if(out_buf == LEFT_ARROW)
			{
				s1->head->direction = HORIZONTAL;
				s1->head->orientation = LEFT_UP;
				buf_full = 1;
			}
			else if(out_buf == RIGHT_ARROW)
			{
				s1->head->direction = HORIZONTAL;
				s1->head->orientation = RIGHT_DOWN;
				buf_full = 1;
			}
		}
	}
	else if( p == MP_T)
	{

	}
		return 0;
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


		printf("procesing\n");
		//printf("R: %d\n", s1->head->row);
		//printf("C: %d\n", s1->head->col);


		if(p == SP_T)
		{

			draw_screen();
			if(counter%10 == 0)
			{
				move_snake(s1);
				printf("running\n");
				flag_colision = update_matrix_snake(s1);
				printf("Flag colision: %d\n", flag_colision);
				printf("matrix updated\n");

				buf_full =0;
			}
			//memcpy(video_mem, double_buffer, SCREEN_SIZE);



		}
		else if( p == MOKB_T)
		{
			draw_screen();
			draw_mouse();
		}
	return;
}
