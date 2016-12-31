
#include "menu.h"


/**
 * @brief bitmap_struct with all bitmaps used in  project
 * */
static Bitmaps_struct *bmp;


static Bitmap *preview_matrix[25] = {NULL};
/**
 * @brief variable to save x position of the mouse
 * */
static unsigned long x_pos_atual = 200;
/**
 * @brief variable to save y position of the mmouse
 * */
static unsigned long y_pos_atual = 200;


void start_variables_menu()
{

	bmp = (Bitmaps_struct*)malloc(sizeof(Bitmaps_struct));
	bmp = (Bitmaps_struct*)getBM();
}


void draw_menu(int mode)
{
	if(mode == 0)
	{
		print_buffer();
		drawbackground(bmp->main_menu,0,0,ALIGN_LEFT);
		update_menu_mouse();

	}else
		if (mode == 1)
		{
			print_buffer();

			drawbackground(bmp->mp_menu,0,0,ALIGN_LEFT);
			update_menu_mouse();
		}


}

void  update_menu_mouse()
{
	drawBitmap(bmp->cursor,x_pos_atual,y_pos_atual,ALIGN_LEFT);
}

void change_body(int opt)
{
	if(opt == 1)
	{
		bmp->body = loadBitmap("/home/proj/res/corpoa.bmp");
	}
	else if(opt == 2)
	{
		bmp->body = loadBitmap("/home/proj/res/corpov.bmp");
	}else if(opt == 3)
	{
		bmp->body = loadBitmap("/home/proj/res/corpo_c.bmp");

	}
	return;
}

void change_body2(int opt)
{
	if(opt == 1)
		{
		bmp->body2 = loadBitmap("/home/proj/res/corpoa.bmp");
		}
		else if(opt == 2)
		{
			bmp->body2 = loadBitmap("/home/proj/res/corpov.bmp");
		}else if(opt == 3)
		{
			bmp->body2 = loadBitmap("/home/proj/res/corpo_c.bmp");

		}
		return;
}

void change_head(int opt)
{
	if(opt ==1)
	{
		bmp->cabeca1hd = loadBitmap("/home/proj/res/cabeca1hd.bmp");
		bmp->cabeca1he = loadBitmap("/home/proj/res/cabeca1he.bmp");
		bmp->cabeca1vc = loadBitmap("/home/proj/res/cabeca1vc.bmp");
		bmp->cabeca1vb = loadBitmap("/home/proj/res/cabeca1vb.bmp");
	}
	else if(opt == 2)
	{
		bmp->cabeca1hd = loadBitmap("/home/proj/res/cabeca2hd.bmp");
		bmp->cabeca1he = loadBitmap("/home/proj/res/cabeca2he.bmp");
		bmp->cabeca1vc = loadBitmap("/home/proj/res/cabeca2vc.bmp");
		bmp->cabeca1vb = loadBitmap("/home/proj/res/cabeca2vb.bmp");
	}else if(opt ==3)
	{
		bmp->cabeca1hd = loadBitmap("/home/proj/res/c_direita.bmp");
		bmp->cabeca1he = loadBitmap("/home/proj/res/c_esquerda.bmp");
		bmp->cabeca1vc = loadBitmap("/home/proj/res/c_cima.bmp");
		bmp->cabeca1vb = loadBitmap("/home/proj/res/c_baixo.bmp");
	}
	return;

}


void draw_choose_snake(int mode)
{
	if(mode == 0)
	{
		print_buffer();
		drawbackground(bmp->choose_main,0,0,ALIGN_LEFT);

		update_menu_mouse();

		return;
	}
	if (mode == 1)
	{
		print_buffer();
		drawbackground(bmp->choose_p1,0,0,ALIGN_LEFT);

				update_menu_mouse();

				return;
	}
	if (mode == 2)
	{
		print_buffer();
		drawbackground(bmp->choose_p2,0,0,ALIGN_LEFT);
		update_menu_mouse();
		return;
	}
}


void update_pos_mouse(unsigned long *x, unsigned long *y)
{

	x_pos_atual += (*x);
	y_pos_atual -= (*y);

	if(x_pos_atual > 1180)
	{
		x_pos_atual = 1180;
	}
	if(x_pos_atual < 80)
		{
			x_pos_atual = 80;
		}
	if(y_pos_atual > 944)
	{
		y_pos_atual = 944;
	}
	if (y_pos_atual < 64)
	{
		y_pos_atual = 64;
	}

	(*y) = y_pos_atual;
	(*x)= x_pos_atual;

}

void draw_time(int hour,int min, int seconds)
{
	int x_inicial =850;
	int y_inicial = 75;
	drawBitmap(bmp->numbers[(hour/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[(hour%10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[10],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial +=40;
	drawBitmap(bmp->numbers[(min/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[(min%10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[10],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[(seconds/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(bmp->numbers[(seconds%10)],x_inicial,y_inicial,ALIGN_LEFT);

}

void draw_instructions(int mode)
{
	if (mode == 0)
	{
		drawbackground(bmp->pausesymb,950,100,ALIGN_LEFT);
		print_buffer();
		return ;
	}
	if (mode == 1)
	{
		drawbackground(bmp->sp_inst,0,0,ALIGN_LEFT);
		print_buffer();
		return;
	}
	if (mode == 2)
	{
		drawbackground(bmp->kbc_inst,0,0,ALIGN_LEFT);
		print_buffer();
		return;
	}
	if (mode == 3)
	{
		drawbackground(bmp->mokb_inst,0,0,ALIGN_LEFT);
		print_buffer();
			return;
	}
	return;
}



void show_points_sp(Snake *s1)
{
	int x_inicial = 640;
	int y = 512;
	int points = s1->size -5;

	drawBitmap(bmp->game_over,350,210,ALIGN_LEFT);
	drawBitmap(bmp->player1,x_inicial-100,y-75,ALIGN_LEFT);

	while(points >= 10)
	{
		drawBitmap(bmp->numbers[points%10],x_inicial,y,ALIGN_LEFT);
		x_inicial -= 40;
		points = points /10;
	}
	drawBitmap(bmp->numbers[points%10],x_inicial,y,ALIGN_LEFT);
	print_buffer();

}


void show_points_mp(Snake *s1, Snake *s2)
{
	int y = 512;
	int x1_in = 320;
	int x2_in = 960;
	int points_s1 = s1->size-5;
	int points_s2 = s2->size-5;

	drawBitmap(bmp->game_over,350,210,ALIGN_LEFT);
	drawBitmap(bmp->player1,x1_in-100,y-75,ALIGN_LEFT);
	drawBitmap(bmp->player2,x2_in-100,y-75,ALIGN_LEFT);
	while(points_s1 >= 10)
		{
		drawBitmap(bmp->numbers[points_s1%10],x1_in,y,ALIGN_LEFT);
			x1_in -= 40;
			points_s1 = points_s1 /10;
		}
	drawBitmap(bmp->numbers[points_s1%10],x1_in,y,ALIGN_LEFT);
		while(points_s2 > 10)
				{
			drawBitmap(bmp->numbers[points_s2%10],x2_in,y,ALIGN_LEFT);
					x2_in -= 40;
					points_s2 = points_s2 /10;
				}
		drawBitmap(bmp->numbers[points_s2%10],x2_in,y,ALIGN_LEFT);
				print_buffer();

}


void draw_preview_snake(Snake *snake_preview, int counter, int body_count)
{
	//draw_snake
	//drawBitmap(double_buffer, body, 20*0+600,200, ALIGN_LEFT);
	//drawBitmap(double_buffer, cabeca1hd, 20*1+200,200, ALIGN_LEFT);
	//print_buffer();

	int i=0;
	segment_snake *seg1 = snake_preview->tail;
	if(body_count == 0)
	{
		do{
			preview_matrix[seg1->col] = bmp->body;

			seg1 = seg1->before;
		}while(seg1!= snake_preview->head);
		preview_matrix[seg1->col] = bmp->cabeca1hd;
	}
	else
	{
			do{
					preview_matrix[seg1->col] = bmp->body2;

					seg1 = seg1->before;
				}while(seg1!= snake_preview->head);
			preview_matrix[seg1->col] = bmp->cabeca2hd;
	}




		i=5;
	while(i<20)	{
		if(preview_matrix[i] != NULL)
		{


			if(preview_matrix[i] == bmp->body || preview_matrix[i] == bmp->body2)
			{
				drawbackground(preview_matrix[i],20*i + 370,300,ALIGN_LEFT);
			}else
			{
				drawBitmap(preview_matrix[i],20*i + 370,300,ALIGN_LEFT);
			}
		}
		i++;
	}
	print_buffer();
	i=0;
	for(i; i<20; i++)
	{
		preview_matrix[i] = NULL;
	}


	if(counter%20 == 0)
	{
		if(snake_preview->head->col < 25)
		{
			move_snake(snake_preview);
		}
		else
		{
			set_snake(snake_preview, -5);
		}
	}



}
