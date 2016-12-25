
#include "man_events.h"

typedef enum {
	MENU_T, SP_T,WAIT_T, MPMENU_T, MOKB_T ,KBC_T, EXIT_T, END_T, PAUSE_T
} states;

typedef enum {
	OPTA, OPTB,OPTB_1,OPTB_2, OPTC, COLISION, START_E ,ESC_PRESSED//mais cenas
} event;

states p=MENU_T;
 event t;


//static states *matrix_states[64][64] = {NULL};   //col x line

static Snake *s1;
static Snake *s2;
static int flag_colision = 0;
static int flag_colision2 = 0;
static int buf_full =0;


//TODO if(2p 2 snakes) {aloca memoria snake 2 cobra}

void check_game_status(states *st, event *ev)
{


	switch(*st){
	case MENU_T:
		{

			if(*ev == OPTA)
			{
				draw_instructions(1);
				printf("fixe\n");
				//game_start(1);
				//printf("COL: %d\n", s1->head->col);
				//printf("ROW: %d\n", s1->head->row);
				/*if(s1->tail == NULL || s1->head == NULL)
					printf("nao deu\n");*/
				//*ev = START_E;
				//TODO draw rules;
				*st = WAIT_T;
			}
			 if (*ev == OPTB)
				{//game_start(2);
				 printf("SIMMMMMMMMM !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				*st = MPMENU_T;
				}
			if (*ev == OPTC)
				*st = EXIT_T;
			break;
		}
	/*case EXIT:
		//sai do programa
		break;*/
	case WAIT_T:
	{
		if(*ev == START_E)
		{
			if(t == OPTA)
			{

				game_start(1);
				*st = SP_T;
			}
			else if(t == OPTB_1)
			{

				game_start(2);
				*st= KBC_T;
			}else if (t== OPTB_2)
			{


				game_start(3);
				*st = MOKB_T;
			}

		}
	}
	case PAUSE_T:
	{
		if(*ev == START_E)
		{
			if(t== OPTA)
			{
				*st = SP_T;
			}else if(t == OPTB_1)
			{

				*st= KBC_T;
			}else if (t== OPTB_2)
			{

				*st = MOKB_T;
			}
		}
		break;
	}
	case SP_T:
		//TODO
	{
		if(*ev == ESC_PRESSED)
		{


			*st = PAUSE_T;
			draw_instructions(0);
		}
		if(*ev == COLISION)
		{

			printf("tenta mudar de estado\n");
			clear_matrix();
			*st = END_T;
		}
		break;
	}
	case MPMENU_T:
	{/*if(*ev == COLISION)
				{
					printf("tenta mudar de estado\n");
					clear_matrix();
					*st = MENU_T;
				}*/
		if(*ev == OPTB_1)
		{
			draw_instructions(2);
			*st = WAIT_T;
		}
		else if (*ev == OPTB_2)
		{
			draw_instructions(3);
			*st = WAIT_T;
		}else if (*ev == OPTC)
		{
			*st = MENU_T;
		}
		break;
	}
	case KBC_T:
		if(*ev == ESC_PRESSED)
				{
					draw_instructions(0);
					*st = PAUSE_T;
				}
		if(*ev == COLISION)
						{
							printf("tenta mudar de estado\n");
							clear_matrix();
							*st = END_T;
						}
		break;
	case MOKB_T:
		if(*ev == ESC_PRESSED)
				{
					draw_instructions(0);
					*st = PAUSE_T;
				}
		if(*ev == COLISION)
								{
									printf("tenta mudar de estado\n");
									clear_matrix();
									*st = END_T;
								}
				break;

	}
	return;

}

int keyboard_event_handler(unsigned long out_buf)
{
	if (p == MENU_T)
	{
		if(out_buf == ESC_CODE)
		{
			return 1;
		}

	}
	if( p== MPMENU_T)
	{
		if(out_buf == ESC_CODE)
		{
			p = MENU_T;
		}
	}

	if(p == END_T)
	{
		if(out_buf == ENTER)
		{
			p = MENU_T;
		}
	}

	if (p == WAIT_T || p == PAUSE_T)
	{
		if(out_buf == ENTER)
		{
			event start_game = START_E;
			check_game_status(&p,&start_game);
			return 0;
		}
	}
	printf("P: %d", p);
	if(p == END_T)
	{
		if(out_buf == ESC_CODE)
		{
			return 1;
		}
	}
	if(p == SP_T || p == MOKB_T)
	{
		if(out_buf == ESC_CODE)
		{
			event aux = ESC_PRESSED;
			check_game_status(&p,&aux);
			return 0;
		}
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
	else if( p == KBC_T)
	{
		if(buf_full == 1)
					return 0;
		if(out_buf == ESC_CODE)
				{
			event aux = ESC_PRESSED;
						check_game_status(&p,&aux);
					return 0;
				}
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
				if(s2->head->direction == HORIZONTAL)
								{
									if(out_buf == W_KEY)
									{
										s2->head->direction = VERTICAL;
										s2->head->orientation = LEFT_UP;
										buf_full = 1;
									}
									else if(out_buf == S_KEY){
										s2->head->direction = VERTICAL;
										s2->head->orientation = RIGHT_DOWN;
										buf_full = 1;
									}
								}
								else
								{
									if(out_buf == A_KEY)
									{
										s2->head->direction = HORIZONTAL;
										s2->head->orientation = LEFT_UP;
										buf_full = 1;
									}
									else if(out_buf == D_KEY)
									{
										s2->head->direction = HORIZONTAL;
										s2->head->orientation = RIGHT_DOWN;
										buf_full = 1;
									}
								}
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

void game_start(int mode)
{
	if (mode == 1) // e modo singleplayer
	{
		Snake *s3 = (Snake*)(malloc(sizeof(Snake)));
						s1 = s3;
						new_snake(5,10,32, s1);
						//remove_snakes_matrix();
						update_matrix_snake(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,1);
						draw_screen();
	}
	if (mode == 2)
	{
		Snake *s3 = (Snake*)(malloc(sizeof(Snake)));
		Snake *s4 = (Snake*)(malloc(sizeof(Snake)));
								s1 = s3;
								s2 = s4;
								new_snake(5,10,10, s1);
								new_snake(5,50,20,s2);
								update_matrix_snakemp(s1,s2,&flag_colision,&flag_colision2);
								new_object_matrix(s1,0);
								new_object_matrix(s1,0);
								new_object_matrix(s1,0);
								draw_screen();
	}
	if (mode == 3)
	{
		Snake *s3 = (Snake*)(malloc(sizeof(Snake)));
								s1 = s3;
								new_snake(5,10,32, s1);
								//remove_snakes_matrix();
								update_matrix_snake(s1,1);

								draw_screen();
	}
	//TODO para multiplayer
}


int timer_event_handler(unsigned short counter)
{

	update_date(&date);
	if(p == EXIT_T)
	{
		return 1;
	}

	if(p == MENU_T)
	{

			int hour = bcd_to_decimal(date.hour);
			int min = bcd_to_decimal(date.min);
			int sec = bcd_to_decimal(date.sec);
			draw_time(hour,min,sec);


		//change_to_start();
		draw_menu(0);
		//update_menu_mouse();
		printf("changed\n");

	}

	if (p == MPMENU_T)
	{
		printf("ENTROU EM MPMENU_T!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		int hour = bcd_to_decimal(date.hour);
		int min = bcd_to_decimal(date.min);
		int sec = bcd_to_decimal(date.sec);
		draw_time(hour,min,sec);
		draw_menu(1);

	}


	/*if(flag_colision == 1 && (p== SP_T || p == KBC_T || p == MOKB_T))
				{

					printf("mudanca estado\n");
					printf("%d\n", p);
					event col_event = COLISION;
					check_game_status(&p, &col_event);
					draw_screen();
					flag_colision = 0;
					printf("p: %d\n",p);
					return 0;


				}*/

		printf("procesing\n");
		//printf("R: %d\n", s1->head->row);
		//printf("C: %d\n", s1->head->col);


		if(p == SP_T || p == MOKB_T)
		{

			if(flag_colision == 1)
			{
				printf("mudanca estado\n");
				printf("%d\n", p);
				event col_event = COLISION;
				check_game_status(&p, &col_event);
				draw_screen();
				flag_colision = 0;

				printf("p: %d\n",p);
				return 0;
			}
			draw_screen();
			if(p == MOKB_T)
			{
				update_menu_mouse();
			}

			if(counter%1200 == 0 && p == SP_T)
			{
				if(bomb_count() == 2)
				{
					remove_bomb();
				}
				new_object_matrix(s1,1);
			}
			if(counter%10 == 0)
			{
				move_snake(s1);
				printf("running\n");
				if(p == MOKB_T)
				{
					flag_colision = update_matrix_snake(s1,1);
				}else
				{flag_colision = update_matrix_snake(s1,0);}
				printf("Flag colision: %d\n", flag_colision);
				printf("matrix updated\n");

				buf_full =0;
			}
			//memcpy(video_mem, double_buffer, SCREEN_SIZE);

			return 0;

		}
		else if(p == KBC_T)
		{

			if(flag_colision == 1)
			{
				printf("mudanca estado\n");
									printf("%d\n", p);
									event col_event = COLISION;
									check_game_status(&p, &col_event);
									draw_screen();
									flag_colision = 0;
									flag_colision2 = 0;
									printf("p: %d\n",p);
									return 0;
			}
			//update_menu_mouse();
			draw_screen();
						if(counter%10 == 0)
						{
							if(flag_colision2 == 0)
							move_snake(s2);
							if(flag_colision == 0)
							move_snake(s1);


							printf("running\n");
							flag_colision = update_matrix_snakemp(s1,s2,&flag_colision,&flag_colision);//nao altera a flag_colision ???

							printf("Flag colision: %d\n", flag_colision);
							printf("matrix updated\n");

							buf_full =0;
						}
						return 0;
		}


}


void mouse_event_handler(unsigned long *packet_mouse)
{
	if(p == SP_T || p == KBC_T)
	{
		return;
	}
	long *x = (long*)malloc(sizeof(long));
	long *y = (long*)malloc(sizeof(long));
	unsigned short *lb = (unsigned short*)malloc(sizeof(unsigned short));
	unsigned short *rb = (unsigned short*)malloc(sizeof(unsigned short));
	printf("ALOCA MEMORIA PACKETS\n");
	if(print_packet(3, packet_mouse, x, y, lb,rb) == 0)
	{
		printf("novoLB: %d\n",*lb);
		update_pos_mouse(x,y);
		//printf("x: %d, y: %d\n",*x,*y);
		if(p == MENU_T)
		{
			if(*x >= 370 && *y >=374 && *x <=(370+542) && *y <= (374+116) && *lb==1 )
			{
				t= OPTA;
				check_game_status(&p,&t);
				return ;
			}
			if(*x >= 370 && *y >=522 && *x <=(370+538) && *y <= (522+112) && *lb==1)
			{
				printf("RECONHECEU OPCAO MULTIPLAYER !!!!!!!!!!!!\n");
				t = OPTB;
				//clear_screen();
				check_game_status(&p,&t);
				printf("PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP: %d!!!\n",p);
				return ;
			}

			if(*x >= 370 && *y >=658 && *x <=(370+542) && *y <= (658+116) && *lb==1 )
				{
					t= OPTC;
					check_game_status(&p,&t);
					return;
				}
		}
		if(p == MPMENU_T)
				{
					if(*x >= 370 && *y >=374 && *x <=(370+542) && *y <= (374+116) && *lb==1  )
					{
						t= OPTB_1;
						flag_colision = 0;
						check_game_status(&p,&t);
						return;
					}
					if(*x >= 370 && *y >=658 && *x <=(370+542) && *y <= (658+116) && *lb==1 )
						{
							t= OPTC;
							check_game_status(&p,&t);
							return;
						}
					if(*x >= 370 && *y >=522 && *x <=(370+542) && *y <= (522+116) && *lb==1)
						{
							t = OPTB_2;
							check_game_status(&p,&t);
							return;
						}
				}
		if(*lb == 1 && p == MOKB_T)//TODO adicionar a verificacao se esta no modo certo
		{
			add_fruit_matrix(*x,*y,s1);

		}
		if(*rb == 1 && p == MOKB_T)
		{
			add_bomb_matrix(*x,*y,s1);
		}




	}
}

