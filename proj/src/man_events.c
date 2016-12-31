
#include "man_events.h"

void check_game_status(states *st, event *ev)
{


	switch(*st){
	case MENU_T:
		{

			if(*ev == OPT_SP)
			{
				new_snake_preview();

				*st = CHOOSE_SN_T;
			}
			 if (*ev == OPT_MP)
				{

				 new_snake_preview();
				*st = MPMENU_T;
				}
			if (*ev == OPT_EXIT)
				*st = EXIT_T;
			break;
		}
	case WAIT_T:
	{
		if(*ev == START_E)
		{
			if(t == OPT_SP)
			{

				game_start(1);
				*st = START_DELAY_T;
			}
			else if(t == OPT_KBC)
			{

				game_start(2);
				*st= START_DELAY_T;
			}else if (t== OPT_MOKB)
			{


				game_start(3);
				*st = START_DELAY_T;
			}

		}
		break;
	}
	case CHOOSE_SN_T:
		if(*ev == START_E)
		{
			if(t== OPT_SP)
			{
				draw_instructions(1);
				//new_snake_preview();
				//*st = SNAKE_PREVIEW_T;
				*st = WAIT_T;
			}else if(t== OPT_KBC)
			{
				draw_instructions(2);
				//new_snake_preview();
				//*st = SNAKE_PREVIEW_T;
				*st = WAIT_T;
			}
			else if( t == OPT_MOKB)
			{
				draw_instructions(3);
				//new_snake_preview()
				//*st = SNAKE_PREVIEW_T;
				*st = WAIT_T;
			}
		}
		break;
	case START_DELAY_T:
		{
			if(*ev == DELAY_E)
			{
				if(t == OPT_SP)
				{
					*st = SP_T;
				}
				else if(t == OPT_KBC)
				{
					*st= KBC_T;
				}
				else if(t == OPT_MOKB){

					*st = MOKB_T;
				}

			}
			break;
		}
	case PAUSE_T:
	{
		if(*ev == START_E)
		{
			if(t== OPT_SP)
			{
				*st = SP_T;
			}else if(t == OPT_KBC)
			{

				*st= KBC_T;
			}else if (t== OPT_MOKB)
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
			points_ingame_sp(s1);
		}
		if(*ev == COLISION)
		{


			clear_matrix();
			*st = END_T;
			show_points_sp(s1);
		}
		break;
	}
	case MPMENU_T:
	{
		if(*ev == OPT_KBC)
		{
			//draw_instructions(2);
			new_snake_preview();

			*st = CHOOSE_SN_T;
		}
		else if (*ev == OPT_MOKB)
		{
			//draw_instructions(3);
			new_snake_preview();
			*st = CHOOSE_SN_T;
		}else if (*ev == OPT_EXIT)
		{
			free(s_preview);
			*st = MENU_T;
		}
		break;
	}
	case KBC_T:
		if(*ev == ESC_PRESSED)
				{
					draw_instructions(0);
					points_ingame_mp(s1,s2);
					*st = PAUSE_T;
				}
		if(*ev == COLISION)
						{

							clear_matrix();
							*st = END_T;
							show_points_mp(s1,s2);
						}
		break;
	case MOKB_T:
		if(*ev == ESC_PRESSED)
				{
					draw_instructions(0);
					points_ingame_sp(s1);
					*st = PAUSE_T;
				}
		if(*ev == COLISION)
								{

									clear_matrix();
									*st = END_T;
									if(second_snake == 0)
									s2 = s1;
									if(second_snake == 1)
									show_points_mp(s2,s1);

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
			if(second_snake == 0 && t == OPT_MOKB)
			{
				second_snake = 1;
				p = CHOOSE_SN_T;

			}
			else
			{
				p = MENU_T;
				second_snake = 0;
			}

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
		if(out_buf == CTRL_MAKE)
		{

			if(s1->boost_time > 0)
			{

				set_boost(s1);
			}
		}
		if(out_buf == CTRL_BREAK)
		{
			if(s1->boost == 1)
			{
				stop_boost(s1);
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
				if(out_buf == CTRL_MAKE)
				{
					if(s2->boost_time > 0)
					{

						set_boost(s2);
					}
				}
				if(out_buf == CTRL_BREAK)
				{
					if(s2->boost == 1)
					{
						stop_boost(s2);
					}
				}
				if(out_buf == SHIFT_MAKE)
				{
					if(s1->boost_time > 0)
					{
						set_boost(s1);
					}
				}
				if(out_buf == SHIFT_BREAK)
				{
					if(s1->boost == 1)
					{
						stop_boost(s1);
					}
				}
	}
		return 0;
}


void game_start(int mode)
{
	if (mode == 1) // e modo singleplayer
	{
		//update_matrix_limits();
		s1 = (Snake*)(malloc(sizeof(Snake)));
						//s1 = s3;
						new_snake(5,28,32, s1);
						//remove_snakes_matrix();
						update_matrix_snake(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,0);
						new_object_matrix(s1,1);
						draw_screen(1);
	}
	else if (mode == 2)
	{
		//update_matrix_limits();
		s1 = (Snake*)(malloc(sizeof(Snake)));
		s2 = (Snake*)(malloc(sizeof(Snake)));
								//s1 = s3;
								//s2 = s4;
								new_snake(5,30,30, s1);
								new_snake(5,40,30,s2);
								update_matrix_snakemp(s1,s2,&flag_colision,&flag_colision2);
								new_object_2_snakes_matrix(s1,s2,0);
								new_object_2_snakes_matrix(s1,s2,0);
								new_object_2_snakes_matrix(s1,s2,0);
								new_object_2_snakes_matrix(s1,s2,1);

								draw_screen(2);
	}
	else if (mode == 3)
	{
		//update_matrix_limits();

			s1 = (Snake*)(malloc(sizeof(Snake)));

				//s1 = s3;
			new_snake(5,28,32, s1);
				//remove_snakes_matrix();
			update_matrix_snake(s1,1);

			draw_screen(1);


	}
	//TODO para multiplayer
}


void new_snake_preview()
{
	s_preview = (Snake*)(malloc(sizeof(Snake)));
	new_snake(5,0,0, s_preview);
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


	}
	if(p == CHOOSE_SN_T)
	{
		if(t == OPT_SP || t== OPT_MOKB)
		{
			draw_choose_snake(0);

			if(body_flag == 1 && head_flag == 1)
			{

				draw_preview_snake(s_preview, counter, 0);

			}
		}
		if (t == OPT_KBC)
		{
			if(choose == 0)
			{
				draw_choose_snake(1);
				if(body_flag == 1)
				{
					draw_preview_snake(s_preview, counter, 0);
				}
			}else
				if(choose == 1)
				{
					draw_choose_snake(2);

					if(body_flag == 1)
					{

						draw_preview_snake(s_preview, counter, 1);
					}
				}
		}

	}


	if (p == MPMENU_T)
	{

		int hour = bcd_to_decimal(date.hour);
		int min = bcd_to_decimal(date.min);
		int sec = bcd_to_decimal(date.sec);
		draw_time(hour,min,sec);
		draw_menu(1);

	}
	if(p == START_DELAY_T)
		{
			if(counter%60 == 0)
			{

			if(t == OPT_SP)
			{

				draw_screen(1);

			}
			else if(t == OPT_KBC)
			{

				draw_screen(2);


			}else if (t== OPT_MOKB)
			{

				draw_screen(1);


			}
			print_number_delay(number_delay);
			if(number_delay == 0)
			{
				number_delay = 3;
				event stop_delay = DELAY_E;
				check_game_status(&p,&stop_delay);
			}
			else
			{
				number_delay--;
			}
			}
		}




		if(p == SP_T || p == MOKB_T)
		{
			points_ingame_sp(s1);

			if(flag_colision == 1)
			{
				draw_screen(1);
				event col_event = COLISION;
				check_game_status(&p, &col_event);
				flag_colision = 0;
				change_head(1);
				return 0;
			}
			draw_screen(1);

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

			if(counter%60 == 0)
			{
				if(s1->boost==1)
				{
					if(s1->boost_time > 0)
						s1->boost_time--;
					else
						stop_boost(s1);
				}
			}
			if(counter%(s1->velocity) == 0)
			{
				move_snake(s1);

				if(p == MOKB_T)
				{
					flag_colision = update_matrix_snake(s1,1);
				}else
				{flag_colision = update_matrix_snake(s1,0);}


				buf_full =0;
			}


			return 0;

		}
		else if(p == KBC_T)
		{

			if(flag_colision == 1 && flag_colision2 == 1)
			{
				draw_screen(2);


									event col_event = COLISION;
									check_game_status(&p, &col_event);
									flag_colision = 0;
									flag_colision2 = 0;

									return 0;
			}
			//update_menu_mouse();
			points_ingame_mp (s1,s2);
			draw_screen(2);
			if(counter%1200 == 0)
			{
					if(bomb_count() == 2)
					{
						remove_bomb();
					}
					new_object_2_snakes_matrix(s1, s2, 1);
			}

			if(counter%60 == 0)
			{
				if(s1->boost==1)
				{
					if(s1->boost_time > 0)
						s1->boost_time--;
					else
						stop_boost(s1);
				}
				if(s2->boost == 1)
				{
					if(s2->boost_time > 0)
						s2->boost_time--;
					else
						stop_boost(s2);
				}
			}

			if(counter%(s2->velocity) == 0)
						{
							if(flag_colision2 == 0)
							move_snake(s2);
							snakes_mp_modify = 1;
						}
						if(counter%(s1->velocity) == 0)
						{
							if(flag_colision == 0)
							move_snake(s1);
							snakes_mp_modify = 1;
						}
						if(snakes_mp_modify == 1)
						{


							update_matrix_snakemp(s1,s2,&flag_colision,&flag_colision2);//nao altera a flag_colision ???


							snakes_mp_modify = 0;
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

	if(print_packet(3, packet_mouse, x, y, lb,rb) == 0)
	{

		update_pos_mouse(x,y);

		if(p == MENU_T)
		{
			if(*x >= 370 && *y >=374 && *x <=(370+542) && *y <= (374+116) && *lb==1 )
			{
				t= OPT_SP;
				check_game_status(&p,&t);
				return ;
			}
			if(*x >= 370 && *y >=522 && *x <=(370+538) && *y <= (522+112) && *lb==1)
			{

				t = OPT_MP;
				//clear_screen();
				check_game_status(&p,&t);

				return ;
			}

			if(*x >= 370 && *y >=658 && *x <=(370+542) && *y <= (658+116) && *lb==1 )
				{
					t= OPT_EXIT;
					check_game_status(&p,&t);
					return;
				}
		}
		if(p == MPMENU_T)
				{
					if(*x >= 370 && *y >=374 && *x <=(370+542) && *y <= (374+116) && *lb==1  )
					{
						t= OPT_KBC;
						flag_colision = 0;
						check_game_status(&p,&t);
						return;
					}
					if(*x >= 370 && *y >=658 && *x <=(370+542) && *y <= (658+116) && *lb==1 )
						{
							t= OPT_EXIT;
							check_game_status(&p,&t);
							return;
						}
					if(*x >= 370 && *y >=522 && *x <=(370+542) && *y <= (522+116) && *lb==1)
						{
							t = OPT_MOKB;
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
		if(p== CHOOSE_SN_T)
		{
			if( t == OPT_KBC)
			{
				if(choose == 0)
				{
					if(body_flag == 1)
					{
						if(*x >= 976 && *y >= 868 && *x <= (976+200) && *y <= (868+74) && *lb ==1)
							{

								head_flag = 0;
								body_flag = 0;
								choose = 1;
								set_snake(s_preview, 5);
								return;
							}
					}
					if(*x >= FIRST_ELEMENT_M && *y >=BODY_HEIGHT_M && *x<=(FIRST_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb ==1)
					{
						choose1 = 1;
						change_body(1);
						body_flag = 1;
						return;
					}
					if(*x>= SECOND_ELEMENT_M && *y >= BODY_HEIGHT_M && *x<= (SECOND_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb == 1)
					{
						choose1 = 2;
						change_body(2);
						body_flag = 1;
						return;
					}
					if(*x >= THIRD_ELEMENT_M && *y>= BODY_HEIGHT_M && *x <= (THIRD_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb == 1)
					{
						choose1 = 3;
						change_body(3);
						body_flag = 1;
						return;
					}
				}
				if(choose == 1)
				{
					if(body_flag == 1)
					{
						if(*x >= 976 && *y >= 868 && *x <= (976+200) && *y <= (868+74) && *lb ==1)
							{

								head_flag = 0;
								body_flag = 0;
								choose = 0;
								choose1 = 0;
								event ev = START_E;
								check_game_status(&p,&ev);
								return;
							}
					}
					if(*x >= FIRST_ELEMENT_M && *y >=BODY_HEIGHT_M && *x<=(FIRST_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb ==1)
					{
						if(choose1 != 1)
						{
							body_flag = 1;
							change_body2(1);
							return;
						}
						return;
					}
					if(*x>= SECOND_ELEMENT_M && *y >= BODY_HEIGHT_M && *x<= (SECOND_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb == 1)
					{
						if (choose1 != 2)
						{
							body_flag = 1;
							change_body2(2);
							return;
						}
						return;
					}
					if(*x >= THIRD_ELEMENT_M && *y>= BODY_HEIGHT_M && *x <= (THIRD_ELEMENT_M + SQUARE_WIDTH) && *y <= (BODY_HEIGHT_M + SQUARE_HEIGHT) && *lb == 1)
					{
						if (choose1 != 3)
						{
							body_flag = 1;
							change_body2(3);
							return;
						}
						return;
					}
				}
			}
			if(t == OPT_SP || t == OPT_MOKB)
			{
				if(head_flag ==1 && body_flag ==1)
				{
				if(*x >= 976 && *y >= 868 && *x <= (976+200) && *y <= (868+74) && *lb ==1)
					{

						head_flag = 0;
						body_flag = 0;
						event ev = START_E;
						check_game_status(&p,&ev);
						return;
					}

								}

				if(*x>= FIRST_ELEMENT && *y>= BODY_HEIGHT && *x <= (FIRST_ELEMENT + SQUARE_WIDTH) && *y <= (BODY_HEIGHT + SQUARE_HEIGHT) && *lb ==1)
				{

					change_body(1);
					body_flag =1;
					return ;
				}
				if(*x>= SECOND_ELEMENT && *y>= BODY_HEIGHT && *x <= (SECOND_ELEMENT + SQUARE_WIDTH) && *y <= (BODY_HEIGHT + SQUARE_HEIGHT) && *lb ==1)
				{
					change_body(2);
					body_flag = 1;
					return;
				}
				if (*x>= THIRD_ELEMENT && *y>= BODY_HEIGHT && *x <= (THIRD_ELEMENT + SQUARE_WIDTH) && *y <= (BODY_HEIGHT + SQUARE_HEIGHT) && *lb == 1)
				{

					change_body(3);
					body_flag = 1;
					return;
				}
				if(*x>= FIRST_ELEMENT && *y >= HEAD_HEIGHT && *x<= (FIRST_ELEMENT + SQUARE_WIDTH) && *y<= (HEAD_HEIGHT + SQUARE_HEIGHT) && *lb ==1)
				{

					change_head(1);
					head_flag =1;
					return;
				}
				if(*x>= SECOND_ELEMENT &&  *y>= HEAD_HEIGHT && *x<= (SECOND_ELEMENT + SQUARE_WIDTH) && *y<= (HEAD_HEIGHT + SQUARE_HEIGHT) && *lb ==1 )
				{
					change_head(2);
					head_flag = 1;
					return;
				}
				if(*x >= THIRD_ELEMENT && *y>= HEAD_HEIGHT && *x<= (THIRD_ELEMENT + SQUARE_WIDTH) && *y <= (HEAD_HEIGHT + SQUARE_HEIGHT) && *lb == 1)
				{

					change_head(3);
					head_flag = 1;
					return;
				}

			}
		}




	}
}

