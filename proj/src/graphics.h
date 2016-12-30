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
#include "objects.h"
#include "date.h"


//Bitmaps
static Bitmap *maca;
static Bitmap *body;
static Bitmap *body2;
static Bitmap *mouse;
static Bitmap *bg;
static Bitmap *bgmp;
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
static Bitmap *kbc_inst;
static Bitmap *mokb_inst;
static Bitmap *pausesymb;
static Bitmap *bomb;
static Bitmap *explosion;
static Bitmap *wall;
static Bitmap *player1;
static Bitmap *player2;
static Bitmap *choose_main;
static Bitmap *choose_p1;
static Bitmap *choose_p2;
static Bitmap *counter1_delay;
static Bitmap *counter2_delay;
static Bitmap *counter3_delay;
static Bitmap *numbers_score[10];
static Bitmap *numbers_back;


void *vg_init(unsigned short mode);
int vg_exit();
void update_pos_mouse(unsigned long *x, unsigned long *y);// pode ser metida no menu.c cuidado com as variaveis x_pos,y_pos_atual
int update_matrix_snake(Snake *s1,int mouse);
void draw_menu(int mode);//pode ser metida no menu.c
int start_mode();
void  update_menu_mouse();//pode ser metida no menu.c cuidado com os bitmaps  static
void change_body(int opt); // pode ser metida no menu.c cuidado com as statics bitmaps
void change_body2(int opt);//pode ser metida no menu.c cuidado com as statics bitmaps
void change_head(int opt);// pode ser metida no menu.c
void clear_matrix();
void draw_screen(int mode);
void draw_choose_snake(int mode); //pode ser metida no menu .c cuidado com a bitmap
void draw_preview_snake(Snake *snake_preview, int counter, int body_count);//pode ??
void new_object_matrix(Snake *s1,unsigned int type);
void new_object_2_snakes_matrix(Snake *s1, Snake *s2, unsigned int type);
void remove_snakes_matrix();
int update_matrix_objects(Game_object *obj, Snake *s1);
int update_matrix_objects_2_snakes(Game_object *obj, Snake *s1, Snake *s2);
int update_matrix_snakemp(Snake *s1,Snake *s2,int *snake1_alive, int *snake2_alive);
void draw_time(int hour,int min, int seconds);//pode ser metida no menu.c cuidado com as bitmaps(array de numeros)
void draw_instructions(int mode);//pode ser metida no menu.c
void show_points_sp(Snake *s1);//pode ser metida no menuc.
void show_points_mp(Snake *s1, Snake *s2);//pode ser metida no menu.c
void points_ingame_sp(Snake *s1); //pode ser metida no menu.c mas como e usado durante o jogo em si talvez tenha mais sentido deixar aqui
void points_ingame_mp (Snake *s1,Snake *s2);//a mesma ideia com points_ingame_sp
int verify_colision_walls_bgmap(int col,int row,int mode);
int add_fruit_matrix(int x, int y,Snake *s1);
int fruit_count();
int bomb_count();
void remove_bomb();
int add_bomb_matrix(int x, int y,Snake *s2);

/**
 * @brief Print the 3, 2, 1 numbers used when a game is starting
 * @param number_delay Number to print (1, 2 or 3)
 */
void print_number_delay(int number_delay);



#endif /* __GRAPHICS_H */
