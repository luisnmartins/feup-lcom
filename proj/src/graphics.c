
#include "graphics.h"

static char *double_buffer;
static char *video_mem; /* Process address to which VRAM is mapped */

static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */


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
	char *video_mem; /* Process address to which VRAM is mapped */


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
	unsigned int vram_size = h_res * v_res * bits_per_pixel / 8; /* VRAM's size, but you can use
	 the frame-buffer size, instead *//* frame-buffer VM address */

	int reg;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if (OK != (reg = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("sys_privctl (ADD_MEM) failed: %d\n", reg);

	/* Map memory */


	video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
	double_buffer = (char *)malloc(h_res*v_res*bits_per_pixel/8*sizeof(char));
	memset(double_buffer, 0, SCREEN_SIZE);
	if (video_mem == MAP_FAILED)
		panic("couldn't map video memory");

	snap = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/snapchat20-16.bmp");
	maca = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/maca20-16.bmp");
	element = loadBitmap("/home/lcom/lcom1617-t4g14/proj/res/segmento20-16.bmp");

	return video_mem;
}


int start_mode()
{

		void *result = vg_init(0x11A);
		memset(double_buffer, 0, SCREEN_SIZE);
		update_matrix_snake(new_snake(5, 10, 32));
		draw_screen();
		memcpy(video_mem, double_buffer, SCREEN_SIZE);

		//drawBitmap(result, snap, 200, 200, ALIGN_LEFT);
		//drawBitmap(result, maca1, 500, 500, ALIGN_LEFT);
		//drawBitmap(result, segment1, 400, 400, ALIGN_LEFT);

		//if(a == NULL)
			//printf("imagem nao carregada\n");
		if(result == NULL)
			return 1;
		else
		{
			video_mem = result;
			return 0;
		}


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

								//paint_black_xpm(xant, yant, square_right);

								if(paint_xpm(x, y, square_right) == 1)
									break;
								else
								{
									xant = xant+19;

								}
								memcpy(video_mem, double_buffer, h_res*v_res*bits_per_pixel/8);
								memset(double_buffer,0, h_res*v_res*bits_per_pixel/8);
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

void draw_screen()
{
	int i_col=0;
	int i_line=0;

	memcpy(video_mem, double_buffer, SCREEN_SIZE);
	memset(double_buffer, 0, SCREEN_SIZE);

	for(i_col; i_col<64; i_col++)
	{
		for(i_line; i_line< 64; i_line++)
		{
			if(matrix_graphics[i_col][i_line] != NULL)
			{
				draw_cell(matrix_graphics[i_col][i_line], i_col, i_line);
			}
		}
	}
}


void draw_cell(Bitmap* bmp, int col, int line)
{

	drawBitmap(double_buffer, bmp, 16*col, 20*line, ALIGN_LEFT);

}



void update_matrix_snake(Snake *s1)
{
	int i=0;
	Segment *seg1 = s1->tail;
	for(i; i<s1->size; i++)
	{
		matrix_graphics[seg1->col][seg1->row] = element;
		seg1 = seg1->before;
	}

}


