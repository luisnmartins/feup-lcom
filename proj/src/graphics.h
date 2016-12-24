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
#include "constants.h"
#include "objects.h"
#include "date.h"


//Bitmaps
static Bitmap *snap;
static Bitmap *maca;
static Bitmap *body;
static Bitmap *body2;
static Bitmap *mouse;
static Bitmap *white;
static Bitmap *bg;
static Bitmap *macaret;
static Bitmap *cabeca1hd;
static Bitmap *cabeca1he;
static Bitmap *cabeca1vc;
static Bitmap *cabeca1vb;
static Bitmap *cabeca2hd;
static Bitmap *cabeca2he;
static Bitmap *cabeca2vc;
static Bitmap *cabeca2vb;
static Bitmap *main_menu;
static Bitmap *mp_menu;
static Bitmap *cursor;
static Bitmap *numbers[11];
static Bitmap *sp_inst;
static Bitmap *pausesymb;


void *vg_init(unsigned short mode);
int vg_exit(void);
int paintPixel(int x,int y,int color);
int paint_xpm(unsigned short xi, unsigned short yi, char *xpm[]);
int clear_pos(unsigned short line, unsigned short col);
void draw_cell(Bitmap* bmp, int col, int line);
void update_pos_mouse(unsigned long *x, unsigned long *y);
int update_matrix_snake(Snake *s1,int mouse);
void draw_menu(int mode);
void  update_menu_mouse();
void clear_matrix();
//void update_matrix_seg(struct Segment *seg);
void new_object_matrix(Snake *s1);
void remove_snakes_matrix();
int update_matrix_objects(Game_object *obj, Snake *s1);
int update_matrix_snakemp(Snake *s1,Snake *s2);
void draw_time(int hour,int min, int seconds);
void draw_instructions(int mode);
void clear_screen();

//paint snake on horizontal direction
int paint_snake_hor(unsigned int x, unsigned int y, unsigned int size, unsigned int right);
int add_fruit_matrix(int x, int y);
int fruit_count();



#endif /* __GRAPHICS_H */
