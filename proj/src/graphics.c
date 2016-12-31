#include "graphics.h"

//#define SCREEN_SIZE 1280*1024*16/8

/**
 * @brief bitmap_struct with all bitmaps used in  project
 * */
static Bitmaps_struct* bmp;

/**
 * @brief global 64 by 64 matrix to virtually divide the screen with 20x16 rectangles
 * */
static Bitmap *matrix_graphics[64][64] = {NULL};   //col x line






void initial_bitmaps()
{
	bmp = (Bitmaps_struct*)malloc(sizeof(Bitmaps_struct));

	bmp->cabeca1hd = loadBitmap("/home/proj/res/cabeca1hd.bmp");
		bmp->cabeca1he = loadBitmap("/home/proj/res/cabeca1he.bmp");
		bmp->cabeca1vc = loadBitmap("/home/proj/res/cabeca1vc.bmp");
		bmp->cabeca1vb = loadBitmap("/home/proj/res/cabeca1vb.bmp");
		bmp->cabeca2hd = loadBitmap("/home/proj/res/cabeca2hd.bmp");
		bmp->cabeca2he = loadBitmap("/home/proj/res/cabeca2he.bmp");
		bmp->cabeca2vc = loadBitmap("/home/proj/res/cabeca2vc.bmp");
		bmp->cabeca2vb = loadBitmap("/home/proj/res/cabeca2vb.bmp");
		bmp->maca = loadBitmap("/home/proj/res/macaq.bmp");
		bmp->body = loadBitmap("/home/proj/res/corpoa.bmp");
		bmp->body2 = loadBitmap("/home/proj/res/corpov.bmp");
		bmp->bg = loadBitmap("/home/proj/res/bg_principal.bmp");
		bmp->bgmp =loadBitmap("/home/proj/res/bg_principal_multi.bmp");
		bmp->main_menu = loadBitmap("/home/proj/res/menu.bmp");
		bmp->cursor = loadBitmap("/home/proj/res/cursor.bmp");
		bmp->numbers[0]  = loadBitmap("/home/proj/res/Number0.bmp");
		bmp->numbers[1]  = loadBitmap("/home/proj/res/Number1.bmp");
		bmp->numbers[2]  = loadBitmap("/home/proj/res/Number2.bmp");
		bmp->numbers[3]  = loadBitmap("/home/proj/res/Number3.bmp");
		bmp->numbers[4]  = loadBitmap("/home/proj/res/Number4.bmp");
		bmp->numbers[5]  = loadBitmap("/home/proj/res/Number5.bmp");
		bmp->numbers[6]  = loadBitmap("/home/proj/res/Number6.bmp");
		bmp->numbers[7]  = loadBitmap("/home/proj/res/Number7.bmp");
		bmp->numbers[8]  = loadBitmap("/home/proj/res/Number8.bmp");
		bmp->numbers[9]  = loadBitmap("/home/proj/res/Number9.bmp");
		bmp->numbers[10] =loadBitmap("/home/proj/res/twodots.bmp");
		bmp->numbers_score[0] = loadBitmap("/home/proj/res/number_score0.bmp");
		bmp->numbers_score[1] = loadBitmap("/home/proj/res/number_score1.bmp");
		bmp->numbers_score[2] = loadBitmap("/home/proj/res/number_score2.bmp");
		bmp->numbers_score[3] = loadBitmap("/home/proj/res/number_score3.bmp");
		bmp->numbers_score[4] = loadBitmap("/home/proj/res/number_score4.bmp");
		bmp->numbers_score[5] = loadBitmap("/home/proj/res/number_score5.bmp");
		bmp->numbers_score[6] = loadBitmap("/home/proj/res/number_score6.bmp");
		bmp->numbers_score[7] = loadBitmap("/home/proj/res/number_score7.bmp");
		bmp->numbers_score[8] = loadBitmap("/home/proj/res/number_score8.bmp");
		bmp->numbers_score[9] = loadBitmap("/home/proj/res/number_score9.bmp");
		bmp->sp_inst = loadBitmap("/home/proj/res/GameRules1.bmp");
		bmp->kbc_inst = loadBitmap("/home/proj/res/GameRules2.bmp");
		bmp->mokb_inst = loadBitmap("/home/proj/res/GameRules3.bmp");
		bmp->bomb = loadBitmap("/home/proj/res/bomb.bmp");
		bmp->explosion = loadBitmap("/home/proj/res/explosions.bmp");
		bmp->mp_menu = loadBitmap("/home/proj/res/menu_mp.bmp");
		bmp->pausesymb =loadBitmap("/home/proj/res/pause.bmp");
		bmp->press_enter = loadBitmap("/home/proj/res/press_enter.bmp");
		bmp->player1 = loadBitmap("/home/proj/res/Player1.bmp");
		bmp->player2 = loadBitmap("/home/proj/res/Player2.bmp");
		bmp->choose_main = loadBitmap("/home/proj/res/choosemain.bmp");
		bmp->choose_p1 = loadBitmap("/home/proj/res/choose_p1.bmp");
		bmp->choose_p2 = loadBitmap("/home/proj/res/choose_p2.bmp");
		bmp->counter1_delay = loadBitmap("/home/proj/res/count1_delay.bmp");
		bmp->counter2_delay = loadBitmap("/home/proj/res/count2_delay.bmp");
		bmp->counter3_delay = loadBitmap("/home/proj/res/count3_delay.bmp");
		bmp->numbers_back =loadBitmap("/home/proj/res/backnumber.bmp");
		bmp->game_over = loadBitmap("/home/proj/res/game_over.bmp");
}


void start_mode()
{

		vg_init(0x11A);

		initial_bitmaps();


}


void points_ingame_sp(Snake *s1)
{
	int x_inicial = 1160;
	int y = 32;
	int points = s1->size -5;

	drawbackground(bmp->numbers_back,x_inicial-80,y,ALIGN_LEFT);
	while(points >= 10)
	{
		drawbackground(bmp->numbers_score[points%10],x_inicial,y,ALIGN_LEFT);
		x_inicial -= 40;
		points = points/10;
	}
	drawbackground(bmp->numbers_score[points%10],x_inicial,y,ALIGN_LEFT);
		print_buffer();

}

void points_ingame_mp (Snake *s1,Snake *s2)
{
	int y = 32;
	int x1_in = 160;
	int x2_in = 1160;
	int points_s1 = s1->size-5;
	int points_s2 = s2->size-5;

	drawbackground(bmp->numbers_back,x1_in-80,y,ALIGN_LEFT);
	drawbackground(bmp->numbers_back,x2_in-80,y,ALIGN_LEFT);
	while(points_s1 >= 10)
	{
		drawbackground(bmp->numbers_score[points_s1%10],x1_in,y,ALIGN_LEFT);
		x1_in -= 40;
		points_s1 = points_s1 /10;
	}
	drawbackground(bmp->numbers_score[points_s1%10],x1_in,y,ALIGN_LEFT);

	while(points_s2 >= 10)
	{
		drawbackground(bmp->numbers_score[points_s2%10],x2_in,y,ALIGN_LEFT);
		x2_in -= 40;
		points_s2 = points_s2 /10;
	}
	drawbackground(bmp->numbers_score[points_s2%10],x2_in,y,ALIGN_LEFT);
	print_buffer();
}




void clear_matrix()
{
	memset(matrix_graphics,(int)NULL,sizeof(matrix_graphics[0][0])*64*64);
}


void draw_screen(int mode)
{
	int i_col=0;
	int i_row=0;

	print_buffer();
	//memset(double_buffer, 0, screen_size);
	if(mode == 1)
	drawbackground( bmp->bg, 0, 0, ALIGN_LEFT);
	else if (mode == 2)
		drawbackground(bmp->bgmp,0,0,ALIGN_LEFT);
	//drawBitmap( maca, 200, 200, ALIGN_LEFT);

		while(i_col < 64)
		{
			while(i_row < 64)
			{
				if(matrix_graphics[i_col][i_row] != NULL)
				{

					if(matrix_graphics[i_col][i_row] == bmp->body || matrix_graphics[i_col][i_row] == bmp->body2)
					{
						drawbackground(matrix_graphics[i_col][i_row],20*i_col,16*i_row,ALIGN_LEFT);
					}else
					{
						drawBitmap( matrix_graphics[i_col][i_row], 20*i_col, 16*i_row, ALIGN_LEFT);

					}

				}
				i_row++;
			}
			i_col++;
			i_row=0;
		}
}





void remove_snakes_matrix()
{
	int i_col =0;
	int i_row = 0;

	while(i_col < 64)
	{
			while(i_row < 64)
			{
				if(matrix_graphics[i_col][i_row] == bmp->body || matrix_graphics[i_col][i_row] == bmp->body2 || matrix_graphics[i_col][i_row] == bmp->cabeca1hd || matrix_graphics[i_col][i_row] == bmp->cabeca1vb || matrix_graphics[i_col][i_row] == bmp->cabeca1he || matrix_graphics[i_col][i_row] == bmp->cabeca1vc || matrix_graphics[i_col][i_row] == bmp->cabeca2hd || matrix_graphics[i_col][i_row] == bmp->cabeca2vb || matrix_graphics[i_col][i_row] == bmp->cabeca2he || matrix_graphics[i_col][i_row] == bmp->cabeca2vc)
				{
					matrix_graphics[i_col][i_row] = NULL;

				}
				i_row++;
			}
			i_col++;
			i_row=0;
	}



}



int verify_colision_walls_bgmap(int col,int row,int mode)
{
	if(mode == 1)
	{
		if(col < 4 || col >= 60 || row < 4 || row >= 60 || (row == 13 && col <= 20) || (col == 12 && (row > 12 && row <= 30)) || (col == 17 && row >= 42) || (row == 42 && (col > 9 && col <= 17)) || (col == 35 &&(row >= 42 )) || (row == 50 && (col >= 49)) || (col == 49 && (row <= 50 && row >=33)) || (col == 43 && (row <= 21)) || (row == 21 &&(col >=35 && col <=51)) || (row == 4 && (col <= 59 && col>= 54 )))
	{
		return 1;
	}
	return 0;
	}
	else if(mode == 2)
	{
		if(col < 4 || col >= 60 || row < 4 || row >= 60 || (col == 12 && (row >= 26 && row <= 33)) || (row ==30 && col <= 12) || (col == 19 && row <= 13 ) || (row == 13 && (col >=15 && col <= 22 )) || (col == 43 && row <= 21) || (row == 21 && (col >= 43 && col <=50)) || (col == 52 && (row >= 34 && row <= 42 )) || (col == 35 && (row >= 42)) ||(row ==48 && (col >= 27 && col <= 35 )) || (row == 4 && (col <= 59 && col>= 54 )) || (row == 4 && (col>= 4 && col <= 9)) )
		{
			return 1;
		}
		return 0;
	}
}

int update_matrix_snake(Snake *s1,int mouse)
{
	remove_snakes_matrix();

	if(s1->head->row > 63 || s1->head->row <0 || s1->head->col > 63 || s1->head->col < 0 )
	{
		return 1;
	}



	int i=0;
	segment_snake *seg1 = s1->tail;



	do
	{


		matrix_graphics[seg1->col][seg1->row] = bmp->body;

		seg1 = seg1->before;
		i++;
	}while(i < s1->size-1);

	if(seg1 == s1->head)
			{


				if(verify_colision_walls_bgmap(seg1->col,seg1->row,1) == 1)
				{
					return 1;
				}
				if(matrix_graphics[seg1->col][seg1->row] == bmp->body || matrix_graphics[seg1->col][seg1->row] == bmp->body2 || matrix_graphics[seg1->col][seg1->row] == bmp->bomb )  //TODO need to add other colisions
				{
					if( matrix_graphics[seg1->col][seg1->row] == bmp->bomb)
					{
						matrix_graphics[seg1->col][seg1->row] = bmp->explosion;
					}

					return 1;
				}
				else if(matrix_graphics[seg1->col][seg1->row] == bmp->maca)
				{
					inc_snake(s1);
					if(mouse == 0)
					new_object_matrix(s1,0);
				}
			}
	if(s1->head->direction == HORIZONTAL)
	{
		if(s1->head->orientation == RIGHT_DOWN)
			matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1hd;
		else
			matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1he;
	}
	else
	{
		if(s1->head->orientation == RIGHT_DOWN)
			matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1vb;
		else
			matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1vc;
	}



	return 0;

}

int update_matrix_snakemp(Snake *s1,Snake *s2,int *snake1_alive, int *snake2_alive)
{
	remove_snakes_matrix();

		if(s1->head->row > 63 || s1->head->row <0 || s1->head->col > 63 || s1->head->col < 0 ||s2->head->row > 63 || s2->head->row <0 || s2->head->col > 63 || s2->head->col < 0 )
		{
			return 1;
		}
		segment_snake *seg1 = s1->tail;
		segment_snake *seg2 = s2->tail;


		int i=0;
		if((*snake1_alive) == 0)
		{





		do
		{

			matrix_graphics[seg1->col][seg1->row] = bmp->body;

			seg1 = seg1->before;
			i++;
		}while(i < s1->size-1);



		}


		i = 0;
		if((*snake2_alive) == 0)
		{


		do
			{


				matrix_graphics[seg2->col][seg2->row] = bmp->body2;

				seg2 = seg2->before;
				i++;
			}while(i < s2->size-1);


		}

		if(*snake1_alive == 0)
		{

			if(seg1 == s1->head)
									{

				if(verify_colision_walls_bgmap(seg1->col,seg1->row,2) == 1)
								{
					matrix_graphics[seg1->col][seg1->row] = NULL;

									(*snake1_alive) = 1;
									return 1;
								}

										if(matrix_graphics[seg1->col][seg1->row] == bmp->body || matrix_graphics[seg1->col][seg1->row] == bmp->body2 ||  matrix_graphics[seg1->col][seg1->row] == bmp->bomb)  //TODO need to add other colisions
										{

											if( matrix_graphics[seg1->col][seg1->row] == bmp->bomb)
											{
												matrix_graphics[seg1->col][seg1->row] = bmp->explosion;
											}
											else
												matrix_graphics[seg1->col][seg1->row] = NULL;

											(*snake1_alive) = 1;

											return 1;
										}
										else if(matrix_graphics[seg1->col][seg1->row] == bmp->maca)
										{
											inc_snake(s1);
											new_object_2_snakes_matrix(s1,s2,0);
										}

										if(s1->head->direction == HORIZONTAL)
											{
												if(s1->head->orientation == RIGHT_DOWN)
													matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1hd;
												else
													matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1he;
											}
											else
											{
												if(s1->head->orientation == RIGHT_DOWN)
													matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1vb;
												else
													matrix_graphics[seg1->col][seg1->row] = bmp->cabeca1vc;
											}
									}
		}
		if(*snake2_alive == 0)
		{

			if(seg2 == s2->head)
					{
				if(verify_colision_walls_bgmap(seg2->col,seg2->row,2) == 1)
								{
					matrix_graphics[seg2->col][seg2->row] = NULL;

																			(*snake2_alive) = 1;
									return 1;
								}
				if(matrix_graphics[seg2->col][seg2->row] == bmp->body || matrix_graphics[seg2->col][seg2->row] == bmp->body2  ||  matrix_graphics[seg2->col][seg2->row] == bmp->bomb)  //TODO need to add other colisions
				{

				if( matrix_graphics[seg2->col][seg2->row] == bmp->bomb)
				{
						matrix_graphics[seg2->col][seg2->row] = bmp->explosion;
														}
														else
															matrix_graphics[seg2->col][seg2->row] = NULL;

														(*snake2_alive) = 1;

														return 1;
													}
						else if(matrix_graphics[seg2->col][seg2->row] == bmp->maca)
						{
							inc_snake(s2);
							new_object_2_snakes_matrix(s1,s2,0);
						}
						if(s2->head->direction == HORIZONTAL)
										{
											if(s2->head->orientation == RIGHT_DOWN)
												matrix_graphics[seg2->col][seg2->row] = bmp->cabeca2hd;
											else
												matrix_graphics[seg2->col][seg2->row] = bmp->cabeca2he;
										}
										else
										{
											if(s2->head->orientation == RIGHT_DOWN)
												matrix_graphics[seg2->col][seg2->row] = bmp->cabeca2vb;
											else
												matrix_graphics[seg2->col][seg2->row] = bmp->cabeca2vc;
										}
					}
		}




		return 0;
}

void new_object_matrix(Snake *s1,unsigned int type)
{
	Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
	do
	{

		new_object(obj,type);

	}while(update_matrix_objects(obj,s1) == 1);
}

void new_object_2_snakes_matrix(Snake *s1, Snake *s2, unsigned int type)
{
	Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
	do
		{

			new_object(obj,type);

		}while(update_matrix_objects_2_snakes(obj,s1, s2) == 1);

}

int update_matrix_objects(Game_object *obj, Snake *s1)
{

	if(obj->col < 4 || obj->col >= 60 || obj->row < 4 || obj->row >= 60)
		{
			return 1;
		}
	if(verify_colision_walls_bgmap(obj->col,obj->row,1) == 1)
	{
		return 1;
	}
	if(matrix_graphics[obj->col][obj->row] != NULL)
		return 1;
	if((abs(obj->row - s1->head->row) < 2 || abs(obj->col - s1->head->col) < 2) || (obj->row == (s1->size-1) || obj->col == (s1->size-1) || obj->row+(s1->size-1) == 63 || obj->col+(s1->size-1) == 63))
	{
		return 1;
	}

	if(obj->name == 0)
	matrix_graphics[obj->col][obj->row] = bmp->maca;
	else if(obj->name == 1)
	{
		matrix_graphics[obj->col][obj->row] = bmp->bomb;
	}
	return 0;

}

int update_matrix_objects_2_snakes(Game_object *obj, Snake *s1, Snake *s2)
{

	if(obj->col < 4 || obj->col >= 60 || obj->row < 4 || obj->row >= 60)
		{
			return 1;
		}
	if(verify_colision_walls_bgmap(obj->col,obj->row,2) == 1)
		{
			return 1;
		}
	if(matrix_graphics[obj->col][obj->row] != NULL)
		return 1;
	if((abs(obj->row - s1->head->row) < 2 || abs(obj->col - s1->head->col) < 2) || (obj->row == (s1->size-1) || obj->col == (s1->size-1) || obj->row+(s1->size-1) == 63 || obj->col+(s1->size-1) == 63))
	{
		return 1;
	}
	if((abs(obj->row - s2->head->row) < 2 || abs(obj->col - s2->head->col) < 2) || (obj->row == (s2->size-1) || obj->col == (s2->size-1) || obj->row+(s2->size-1) == 63 || obj->col+(s2->size-1) == 63))
		{
			return 1;
		}

	if(obj->name == 0)
	matrix_graphics[obj->col][obj->row] = bmp->maca;
	else if(obj->name == 1)
	{
		matrix_graphics[obj->col][obj->row] = bmp->bomb;
	}
	return 0;

}

int add_fruit_matrix(int x, int y,Snake *s1)
{

	if(x > 1280 || x < 0 || y >1024 || y <0 )
		return 1;
	else
	{
		int col = (x/20);
		int row = (y/16);
		Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
		new_object(obj,0);
		obj->col = col;
		obj->row = row;


		if (matrix_graphics[obj->col][obj->row] != NULL)
				return 1;
		if(col < 4 || col >= 60 || row < 4 || row >=60)
		{
			return 1;
		}
		if(verify_colision_walls_bgmap(col,row,1) == 1)
			{
				return 1;
			}
		if(((abs(obj->row - s1->head->row) < 2 && abs(obj->col - s1->head->col) < 2)) || (obj->row == (s1->size-1) || obj->col == (s1->size-1) || obj->row+(s1->size-1) == 63 || obj->col+(s1->size-1) == 63))
			{
				return 1;
			}

		if(fruit_count() < 3)
		{
			matrix_graphics[obj->col][obj->row] = bmp->maca;
			return 0;
		}

	}



}

int add_bomb_matrix(int x, int y,Snake *s1)
{

	if(x > 1280 || x < 0 || y >1024 || y <0 )
		return 1;
	else
	{
		int col = (x/20);
		int row = (y/16);
		Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
		new_object(obj,1);
		obj->col = col;
		obj->row = row;


		if (matrix_graphics[obj->col][obj->row] != NULL)
				return 1;
		if(col < 4 || col >= 60 || row < 4 || row >=60)
		{
			return 1;
		}
		if(verify_colision_walls_bgmap(col,row,1) == 1)
					{
						return 1;
					}
		if((abs(obj->row - s1->head->row) < 2 || abs(obj->col - s1->head->col) < 2) || (obj->row == (s1->size-1) || obj->col == (s1->size-1) || obj->row+(s1->size-1) == 63 || obj->col+(s1->size-1) == 63))
					{
						return 1;
					}

		if(bomb_count() == fruit_count())
		{
			remove_bomb();
			matrix_graphics[obj->col][obj->row] = bmp->bomb;
						return 0;
		}
		if(bomb_count() < fruit_count())
		{
			matrix_graphics[obj->col][obj->row] = bmp->bomb;
			return 0;
		}

	}



}

void remove_bomb()
{
	int i_col = 0;
		int i_row = 0;
		while(i_col < 64)
			{
					while(i_row < 64)
					{
						if(matrix_graphics[i_col][i_row] == bmp->bomb)
						{
							matrix_graphics[i_col][i_row] = NULL;
							return;

						}
						i_row++;
					}
					i_col++;
					i_row=0;
			}

}

int fruit_count()
{
	int how_many = 0;
	int i_col = 0;
	int i_row = 0;
	while(i_col < 64)
		{
				while(i_row < 64)
				{
					if(matrix_graphics[i_col][i_row] == bmp->maca)
					{
						how_many++;

					}
					i_row++;
				}
				i_col++;
				i_row=0;
		}
	return how_many;
}

int bomb_count()
{
	int how_many = 0;
	int i_col = 0;
	int i_row = 0;
	while(i_col < 64)
		{
				while(i_row < 64)
				{
					if(matrix_graphics[i_col][i_row] == bmp->bomb)
					{
						how_many++;

					}
					i_row++;
				}
				i_col++;
				i_row=0;
		}
	return how_many;
}

void print_number_delay(int number_delay)
{
	if (number_delay == 1)
	{
		drawBitmap(bmp->counter1_delay,592,419,ALIGN_LEFT);
		print_buffer();
	}else if(number_delay == 2)
	{
		drawBitmap(bmp->counter2_delay,592,419,ALIGN_LEFT);
				print_buffer();
	}
	else if(number_delay == 3)
	{
		drawBitmap(bmp->counter3_delay,592,419,ALIGN_LEFT);
		print_buffer();
	}
}




Bitmaps_struct* getBM()
{
	return bmp;
}




