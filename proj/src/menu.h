

#include "graphics.h"
#include "constants.h"



void start_variables_menu();

void update_pos_mouse(unsigned long *x, unsigned long *y);// pode ser metida no menu.c cuidado com as variaveis x_pos,y_pos_atual
void draw_menu(int mode);//pode ser metida no menu.c
void  update_menu_mouse();//pode ser metida no menu.c cuidado com os bitmaps  static
void change_body(int opt); // pode ser metida no menu.c cuidado com as statics bitmaps
void change_body2(int opt);//pode ser metida no menu.c cuidado com as statics bitmaps
void change_head(int opt);// pode ser metida no menu.c

void draw_choose_snake(int mode); //pode ser metida no menu .c cuidado com a bitmap
void draw_preview_snake(Snake *snake_preview, int counter, int body_count);//pode ??
void draw_time(int hour,int min, int seconds);//pode ser metida no menu.c cuidado com as bitmaps(array de numeros)
void draw_instructions(int mode);//pode ser metida no menu.c
void show_points_sp(Snake *s1);//pode ser metida no menuc.
void show_points_mp(Snake *s1, Snake *s2);//pode ser metida no menu.c

