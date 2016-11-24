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



	  int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
	  int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
	  int err = (dx>dy ? dx : -dy)/2, e2;

	  for(;;){
	    paintPixel(x1,y1,color);
	    if (x1==x2 && y1==y2) break;
	    e2 = err;
	    if (e2 >-dx) { err -= dy; x1 += sx; }
	    if (e2 < dy) { err += dx; y1 += sy; }
	  }

	return 0;
}


