#ifndef __GRAPHICS_H
#define __GRAPHICS_H



#include <minix/syslib.h>
#include <minix/drivers.h>
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
#include "constants.h"


//Bitmaps
static Bitmap *snap;
static Bitmap *maca;
static Bitmap *element;



void *vg_init(unsigned short mode);
int vg_exit(void);
int paintPixel(int x,int y,int color);
int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[]);
int clear_pos(unsigned short line, unsigned short col);
void draw_cell(Bitmap* bmp, int col, int line);
void update_matrix_snake(Snake *s1);
void update_matrix_seg(segment_t *seg);

//paint snake on horizontal direction
int paint_snake_hor(unsigned int x, unsigned int y, unsigned int size, unsigned int right);
int move_snake(unsigned int x, unsigned int y, unsigned short hor,unsigned int xant);


#endif /* __GRAPHICS_H */
