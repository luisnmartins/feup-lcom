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

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */




int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}


void *vg_init(unsigned short mode)
{


	 struct reg86u r;

	  r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	  r.u.w.bx = 1<<14|mode; // set bit 14: linear framebuffer
	  r.u.b.intno = 0x10;
	  if( sys_int86(&r) != OK ) {
	      printf("set_vbe_mode: sys_int86() failed \n");
	      return NULL;
	  }


	struct mem_range mr;
	unsigned int vram_base = VRAM_PHYS_ADDR;  /* VRAM's physical addresss */
	unsigned int vram_size = H_RES*V_RES*BITS_PER_PIXEL/8;  /* VRAM's size, but you can use
	                            the frame-buffer size, instead */       /* frame-buffer VM address */




	int reg;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (reg = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	   panic("sys_privctl (ADD_MEM) failed: %d\n", reg);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

	if(video_mem == MAP_FAILED)
	   panic("couldn't map video memory");

	h_res = H_RES;
	v_res = V_RES;
	bits_per_pixel = BITS_PER_PIXEL;

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

int make_line(float x1,float x2,float y1,float y2, unsigned long color)
{

	//using DDA algorithm and the tutorial from https://www.tutorialspoint.com/computer_graphics/line_generation_algorithm.htm

	int comp_x, comp_y, p, delta_max, i;
	float x, y, delta_y, delta_x;

		//calculating the distance between points in x and y coordinates
		comp_x = abs(x1 - x2);
	    comp_y = abs(y1 - y2);

	    //setting as step the greater value between comp_x and comp_y because
	    if (abs(comp_x) > abs(comp_y))
	       delta_max = abs(comp_x);
	    else
	    	delta_max = abs(comp_y);

	    //setting the step to x axis and y axis
	    delta_x = (float)comp_x/delta_max;
	    delta_y = (float)comp_y/delta_max;



	    for(i=0; i<delta_max; i++)
	    {
	    	x1 = x1+delta_x;
	    	y1 = y1+delta_y;
	    	if(paintPixel(round(x1), round(y1), color)!= 0)
	    		return 1;
	    }

	return 0;
}


