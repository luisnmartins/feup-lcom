


#include <minix/syslib.h>
#include <minix/drivers.h>
//#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>
#include "vbe.h"
#include "video_gr.h"
#include "pixmap.h"
#include "timer.h"
#include "keyboard.h"
#include "snake.h"
#include "Bitmap.h"


#define H_RES             1280
#define V_RES		  1024
#define BITS_PER_PIXEL	  16

static Bitmap *matrix_graphics[64][64];

//Bitmaps
static Bitmap *snap;
static Bitmap *maca1;
static Bitmap *segment1;



void *vg_init(unsigned short mode);
int vg_exit(void);
int paintPixel(int x,int y,int color);
int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[]);
int clear_pos(unsigned short line, unsigned short col);

//paint snake on horizontal direction
int paint_snake_hor(unsigned int x, unsigned int y, unsigned int size, unsigned int right);
int move_snake(unsigned int x, unsigned int y, unsigned short hor,unsigned int xant);

