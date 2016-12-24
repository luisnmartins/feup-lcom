#include "graphics.h"

static char *double_buffer;
static char *video_mem; /* Process address to which VRAM is mapped */
static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static Bitmap *matrix_graphics[64][64] = {NULL};   //col x line
static unsigned long x_pos_atual = 200;
static unsigned long y_pos_atual = 200;

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00; /* Set Video Mode function */
	reg86.u.b.al = 0x03; /* 80x25 text mode*/

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}



void *vg_init(unsigned short mode) {

	struct reg86u r;
	vbe_mode_info_t v;
	struct mem_range mr;


	vbe_get_mode_info(mode,&v);

	h_res = v.XResolution;
	v_res = v.YResolution;
	bits_per_pixel = v.BitsPerPixel;

	r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = 1 << 14 | mode; // set bit 14: linear framebuffer
	r.u.b.intno = 0x10;
	if (sys_int86(&r) != OK) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}


	unsigned int vram_base = v.PhysBasePtr; /* VRAM's physical addresss */
	unsigned int vram_size = h_res * v_res * bits_per_pixel/8; /* VRAM's size, but you can use
	 the frame-buffer size, instead *//* frame-buffer VM address */

	int reg;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if (OK != (reg = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("sys_privctl (ADD_MEM) failed: %d\n", reg);

	/* Map memory */


	video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
	double_buffer = (short *)malloc(h_res*v_res*bits_per_pixel/8);
	memset(double_buffer, 0, SCREEN_SIZE);
	if (video_mem == MAP_FAILED)
		panic("couldn't map video memory");

	snap = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/snapchat20-16.bmp");
	cabeca1hd = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca1hd.bmp");
	cabeca1he = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca1he.bmp");
	cabeca1vc = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca1vc.bmp");
	cabeca1vb = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca1vb.bmp");
	cabeca2hd = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca2hd.bmp");
	cabeca2he = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca2he.bmp");
	cabeca2vc = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca2vc.bmp");
	cabeca2vb = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cabeca2vb.bmp");
	maca = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/macaq.bmp");
	body = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/corpoa.bmp");
	body2 = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/corpov.bmp");
	white = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/3white.bmp");
	bg = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/bg.bmp");
	main_menu = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/menu.bmp");
	cursor = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/cursor.bmp");
	numbers[0]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number0.bmp");
	numbers[1]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number1.bmp");
	numbers[2]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number2.bmp");
	numbers[3]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number3.bmp");
	numbers[4]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number4.bmp");
	numbers[5]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number5.bmp");
	numbers[6]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number6.bmp");
	numbers[7]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number7.bmp");
	numbers[8]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number8.bmp");
	numbers[9]  = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/Number9.bmp");
	numbers[10] =loadBitmap("home/lcom/lcom1617-t4g14/proj/res/twodots.bmp");
	sp_inst = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/GameControllersSP.bmp");
	mp_menu = loadBitmap("home/lcom/lcom1617-t4g14/proj/res/menu_mp.bmp");

	//memset(video_mem, 1, SCREEN_SIZE);
	//drawBitmap(video_mem, maca, 100, 100, ALIGN_LEFT);
	return video_mem;
}


int start_mode()
{

		void *result = vg_init(0x11A);


		//memcpy(video_mem, double_buffer, SCREEN_SIZE);

		if(result == NULL)
			return 1;
		else
		{
			video_mem = result;
			return 0;
		}


}
void clear_screen()
{
	memset(video_mem,0,SCREEN_SIZE);
}


int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[])
{
	int largura, altura,a,b;
	char *ptr_img = (char *)read_xpm(xpm, &largura, &altura);

	if(xi >= h_res || yi >= v_res)
	{
		return 1;
	}

	for (a = 0; a < altura; a++)
	{
		for (b = 0; b < largura; b++) {
			paintPixel(xi + b, yi + a, *(ptr_img + a * largura + b));
		}
	}
	free(ptr_img);

}



int paintPixel(int x,int y,int color)
{
	if(x<0 || x>h_res || y<0 || y>v_res)
	{
		printf("Coordinates not valid\n");
		return 1;
	}


	char *video_mptr = double_buffer;


	unsigned bytes_pixel = bits_per_pixel/8;

	video_mptr +=  (h_res*y + x) * bytes_pixel;

	*video_mptr = color;

	return 0;

}




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
void clear_matrix()
{
	memset(matrix_graphics,NULL,sizeof(matrix_graphics[0][0])*64*64);
}

int clear_pos(unsigned short line, unsigned short col)
{
	if (line >=0 && line <= 63 && col >= 0 && col <= 63)
	{
		matrix_graphics[line][col] = NULL;
		return 0;
	}
	else
		return 1;
}
void draw_menu(int mode)
{
	if(mode == 0)
	{
		memcpy(video_mem,double_buffer, SCREEN_SIZE);
	//memset(double_buffer,0,SCREEN_SIZE);
	drawbackground(double_buffer,main_menu,0,0,ALIGN_LEFT);
	update_menu_mouse();
	//drawbackground(double_buffer, body, x_pos_atual, y_pos_atual, ALIGN_LEFT);

	}else
		if (mode == 1)
		{
			memcpy(video_mem,double_buffer, SCREEN_SIZE);
			//memset(double_buffer,0,SCREEN_SIZE);
			drawbackground(double_buffer,mp_menu,0,0,ALIGN_LEFT);
			update_menu_mouse();
			//drawbackground(double_buffer, body, x_pos_atual, y_pos_atual, ALIGN_LEFT);
		}


}
void draw_time(int hour,int min, int seconds)
{
	//memcpy(video_mem,double_buffer,SCREEN_SIZE);
	int x_inicial =850;
	int y_inicial = 75;
	drawBitmap(double_buffer,numbers[(hour/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[(hour%10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[10],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial +=40;
	drawBitmap(double_buffer,numbers[(min/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[(min%10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[10],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[(seconds/10)],x_inicial,y_inicial,ALIGN_LEFT);
	x_inicial += 40;
	drawBitmap(double_buffer,numbers[(seconds%10)],x_inicial,y_inicial,ALIGN_LEFT);

}
void  update_menu_mouse()
{
	drawBitmap(double_buffer,cursor,x_pos_atual,y_pos_atual,ALIGN_LEFT);
}

void draw_instructions(int mode)
{
	if (mode == 1)
	{
		drawbackground(double_buffer,sp_inst,0,0,ALIGN_LEFT);
		memcpy(video_mem,double_buffer,SCREEN_SIZE);
	}
}

void draw_screen()
{
	int i_col=0;
	int i_row=0;

	memcpy(video_mem, double_buffer, SCREEN_SIZE);
	//memset(double_buffer, 0, SCREEN_SIZE);
	drawbackground(double_buffer, bg, 0, 0, ALIGN_LEFT);
	//drawBitmap(double_buffer, maca, 200, 200, ALIGN_LEFT);

		while(i_col < 64)
		{
			while(i_row < 64)
			{
				if(matrix_graphics[i_col][i_row] != NULL)
				{
					if(matrix_graphics[i_col][i_row] == body || matrix_graphics[i_col][i_row] == body2)
					{
						drawbackground(double_buffer,matrix_graphics[i_col][i_row],20*i_col,16*i_row,ALIGN_LEFT);
					}else
					{
						drawBitmap(double_buffer, matrix_graphics[i_col][i_row], 20*i_col, 16*i_row, ALIGN_LEFT);
					printf("linha: %d\n", i_row);
					printf("coluna: %d\n", i_col);
					}

				}
				i_row++;
			}
			i_col++;
			i_row=0;
		}
		//drawBitmap(double_buffer, body, x_pos_atual, y_pos_atual, ALIGN_LEFT);
		printf("acabou screen\n");
		//memcpy(video_mem, double_buffer, SCREEN_SIZE);
}


void update_pos_mouse(unsigned long *x, unsigned long *y)
{

	x_pos_atual += (*x);
	y_pos_atual -= (*y);

	(*y) = y_pos_atual;
	(*x)= x_pos_atual;

}


void remove_snakes_matrix()
{
	int i_col =0;
	int i_row = 0;

	while(i_col < 64)
	{
			while(i_row < 64)
			{
				if(matrix_graphics[i_col][i_row] == body || matrix_graphics[i_col][i_row] == body2 || matrix_graphics[i_col][i_row] ==cabeca1hd || matrix_graphics[i_col][i_row] ==cabeca1vb || matrix_graphics[i_col][i_row] ==cabeca1he || matrix_graphics[i_col][i_row] ==cabeca1vc || matrix_graphics[i_col][i_row] ==cabeca2hd || matrix_graphics[i_col][i_row] ==cabeca2vb || matrix_graphics[i_col][i_row] ==cabeca2he || matrix_graphics[i_col][i_row] ==cabeca2vc)
				{
					matrix_graphics[i_col][i_row] = NULL;

				}
				i_row++;
			}
			i_col++;
			i_row=0;
	}

	printf("snake removed\n");

}

int update_matrix_snake(Snake *s1,int mouse)
{
	remove_snakes_matrix();

	//printf("okokok3\n");
	//printf("ROW: %d\n", s1->head->row);
		//		printf("COLD: %d\n", s1->head->col);
	if(s1->head->row > 63 || s1->head->row <0 || s1->head->col > 63 || s1->head->col < 0 )
	{	printf("merdou\n");
		return 1;
	}



	int i=0;
	segment_snake *seg1 = s1->tail;
	printf("criou segmento");
	printf("tail cenas: %d\n", seg1->col);


	do
	{
		printf("seg1 col: %d\n", seg1->col);
		printf("seg1 row: %d\n", seg1->row);
		/*if(seg1 == s1->head)
				{
					if(matrix_graphics[seg1->col][seg1->row] == body)  //TODO need to add other colisions
					{
						printf("colision\n");
						return 1;
					}
					else if(matrix_graphics[seg1->col][seg1->row] == maca)
					{
						inc_snake(s1);
						new_object_matrix(s1);
					}
				}*/

		matrix_graphics[seg1->col][seg1->row] = body;

		seg1 = seg1->before;
		i++;
	}while(i < s1->size-1);

	if(seg1 == s1->head)
			{
				if(matrix_graphics[seg1->col][seg1->row] == body || matrix_graphics[seg1->col][seg1->row] == body2)  //TODO need to add other colisions
				{
					printf("colision\n");
					return 1;
				}
				else if(matrix_graphics[seg1->col][seg1->row] == maca)
				{
					inc_snake(s1);
					if(mouse == 0)
					new_object_matrix(s1);
				}
			}
	if(s1->head->direction == HORIZONTAL)
	{
		if(s1->head->orientation == RIGHT_DOWN)
			matrix_graphics[seg1->col][seg1->row] = cabeca1hd;
		else
			matrix_graphics[seg1->col][seg1->row] = cabeca1he;
	}
	else
	{
		if(s1->head->orientation == RIGHT_DOWN)
			matrix_graphics[seg1->col][seg1->row] = cabeca1vb;
		else
			matrix_graphics[seg1->col][seg1->row] = cabeca1vc;
	}


	printf("acabou\n");
	return 0;

}

int update_matrix_snakemp(Snake *s1,Snake *s2)
{
	remove_snakes_matrix();

		//printf("okokok3\n");
		//printf("ROW: %d\n", s1->head->row);
			//		printf("COLD: %d\n", s1->head->col);
		if(s1->head->row > 63 || s1->head->row <0 || s1->head->col > 63 || s1->head->col < 0 ||s2->head->row > 63 || s2->head->row <0 || s2->head->col > 63 || s2->head->col < 0 )
		{	printf("merdou\n");
			return 1;
		}



		int i=0;
		segment_snake *seg1 = s1->tail;
		printf("criou segmento");
		printf("tail cenas: %d\n", seg1->col);


		do
		{
			printf("seg1 col: %d\n", seg1->col);
			printf("seg1 row: %d\n", seg1->row);
			/*if(seg1 == s1->head)
					{
						if(matrix_graphics[seg1->col][seg1->row] == body)  //TODO need to add other colisions
						{
							printf("colision\n");
							return 1;
						}
						else if(matrix_graphics[seg1->col][seg1->row] == maca)
						{
							inc_snake(s1);
							new_object_matrix(s1);
						}
					}*/

			matrix_graphics[seg1->col][seg1->row] = body;

			seg1 = seg1->before;
			i++;
		}while(i < s1->size-1);


		i = 0;
		segment_snake *seg2 = s2->tail;
		do
			{
				printf("seg2 col: %d\n", seg2->col);
				printf("seg2 row: %d\n", seg2->row);
				matrix_graphics[seg2->col][seg2->row] = body2;

				seg2 = seg2->before;
				i++;
			}while(i < s2->size-1);
		if(seg1 == s1->head)
						{
							if(matrix_graphics[seg1->col][seg1->row] == body || matrix_graphics[seg1->col][seg1->row] == body2)  //TODO need to add other colisions
							{
								printf("colision\n");
								return 1;
							}
							else if(matrix_graphics[seg1->col][seg1->row] == maca)
							{
								inc_snake(s1);
								new_object_matrix(s1);
							}
						}

				if(s1->head->direction == HORIZONTAL)
					{
						if(s1->head->orientation == RIGHT_DOWN)
							matrix_graphics[seg1->col][seg1->row] = cabeca1hd;
						else
							matrix_graphics[seg1->col][seg1->row] = cabeca1he;
					}
					else
					{
						if(s1->head->orientation == RIGHT_DOWN)
							matrix_graphics[seg1->col][seg1->row] = cabeca1vb;
						else
							matrix_graphics[seg1->col][seg1->row] = cabeca1vc;
					}

			if(seg2 == s2->head)
					{
						if(matrix_graphics[seg2->col][seg2->row] == body2 || matrix_graphics[seg2->col][seg2->row] == body)  //TODO need to add other colisions
						{
							printf("colision\n");
							return 1;
						}
						else if(matrix_graphics[seg2->col][seg2->row] == maca)
						{
							inc_snake(s2);
							new_object_matrix(s2);
						}
					}

			if(s2->head->direction == HORIZONTAL)
				{
					if(s2->head->orientation == RIGHT_DOWN)
						matrix_graphics[seg2->col][seg2->row] = cabeca2hd;
					else
						matrix_graphics[seg2->col][seg2->row] = cabeca2he;
				}
				else
				{
					if(s2->head->orientation == RIGHT_DOWN)
						matrix_graphics[seg2->col][seg2->row] = cabeca2vb;
					else
						matrix_graphics[seg2->col][seg2->row] = cabeca2vc;
				}

		printf("acabou\n");
		return 0;
}

void new_object_matrix(Snake *s1)
{
	Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
	do
	{

		new_object(obj,0);

	}while(update_matrix_objects(obj,s1) == 1);
}


int update_matrix_objects(Game_object *obj, Snake *s1)
{

	if(obj->col < 4 || obj->col >= 60 || obj->row < 4 || obj->row >= 60)
		{
			return 1;
		}
	if(matrix_graphics[obj->col][obj->row] != NULL)
		return 1;
	if((abs(obj->row - s1->head->row) < 2 || abs(obj->col - s1->head->col) < 2) || (obj->row == (s1->size-1) || obj->col == (s1->size-1) || obj->row+(s1->size-1) == 63 || obj->col+(s1->size-1) == 63))
	{
		return 1;
	}

	matrix_graphics[obj->col][obj->row] = maca;
	return 0;

}
int add_fruit_matrix(int x, int y)
{
	printf("x: %d, y: %d\n",x,y);
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

		printf("nova_coluna:%d  novarow:%d  \n",col,row);
		if (matrix_graphics[obj->col][obj->row] != NULL)
				return 1;
		if(col < 4 || col >= 60 || row < 4 || row >=60)
		{
			return 1;
		}

		if(fruit_count() < 3)
		{
			matrix_graphics[obj->col][obj->row] = maca;
			return 0;
		}

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
					if(matrix_graphics[i_col][i_row] == maca)
					{
						how_many++;

					}
					i_row++;
				}
				i_col++;
				i_row=0;
		}
	printf("quantods:%d\n", how_many);
	return how_many;
}
