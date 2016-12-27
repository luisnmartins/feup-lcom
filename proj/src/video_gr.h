#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/*#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8
#define ABSOL(a) ((a) >= 0 ? (a) : -(a))

static unsigned h_res; /* Horizontal screen resolution in pixels */
//static unsigned v_res; /* Vertical screen resolution in pixels */
//static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>
#include "vbe.h"


/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
//void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
//int vg_exit(void);

 /** @} end of video_gr */




//int paintPixel(int x,int y,int color);
//int make_line(float x1,float x2,float y1,float y2, unsigned long color);

//int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[]);

//int paint_black_xpm(unsigned short xi, unsigned short yi, char *xpm[]);


//Funcoes de execucao

//int start_mode();

 
#endif /* __VIDEO_GR_H */
