#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "video_gr.h"
#include <math.h>

#include "vbe.h"

#define round(x) ((x)>=0? (long) ((x)+0.5): (long)((x)-0.5))

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */

/* Private global variables */

static char *video_mem; /* Process address to which VRAM is mapped */

static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

static char *double_buffer;

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

	if (video_mem == MAP_FAILED)
		panic("couldn't map video memory");


	double_buffer = (char*) malloc(h_res*v_res*(bits_per_pixel/8) *sizeof(char));
	return video_mem;
}

int paintPixel(int x,int y,int color)
{
	if(x<0 || x>h_res || y<0 || y>v_res)
	{
		printf("Coordinates not valid\n");
		return 1;
	}


	char *video_mptr = video_mem;


	unsigned bytes_pixel = bits_per_pixel/8;

	video_mptr +=  (h_res*y + x) * bytes_pixel;

	*video_mptr = color;

	return 0;

}


int paintPixelaux ( int x, int y, int color)
{
	if(x<0 || x>h_res || y<0 || y>v_res)
		{
			printf("Coordinates not valid\n");
			return 1;
		}

	char *pos_to_print = double_buffer;

	unsigned bytes_pixel = bits_per_pixel/8;

	pos_to_print +=  (h_res*y + x) * bytes_pixel;

	*pos_to_print = color;

	return 0;

}

int make_line(float x1, float x2, float y1, float y2, unsigned long color) {

	int dx, dy; /* Dx and Dy values for the line */
	int t;
	float n_inc; //numero de  incrementos que ocorre, obtem-se do delta de maior valor
	float xinc, yinc; //o incremento que x e y vao ter em cada iteracao que pinta


	dx = x2-x1; //deltax
	dy = y2-y1; //deltay

	if(ABSOL(dx) > ABSOL(dy))
		n_inc = ABSOL(dx); // determina o delta com maior valor e mete o em steps
	else
		n_inc = ABSOL(dy);

	xinc = dx/ n_inc; //o x a pintar vai ser obtido pela razao entre o seu delta e numero de passos, pode nao dar numero inteiro mas nao interessa porque sao feitos arredondamentos
	yinc = dy / n_inc; // o x a pintar vai ser obtido pela razao entre o seu delta e numero de passos, pode nao dar numero inteiro mas nao interessa porque sao feitos arredondamentos
	paintPixel(x1,x2,color); // pinta o primeiro pixel da linha;
	for (t = 0; t < n_inc; t++)
	{
		x1 +=  xinc;
		y1 +=  yinc;
		paintPixel(round(x1),round(y1),color);
	}

 //Baseado no algoritmo de DDA

	return 0;
}
int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[])
{
	int largura, altura,a,b;
	char *ptr_img = (char *)read_xpm(xpm, &largura, &altura);


	for (a = 0; a < altura; a++)
	{
		for (b = 0; b < largura; b++) {
			paintPixel(xi + b, yi + a, *(ptr_img + a * largura + b));
		}
	}
	free(ptr_img);

}



