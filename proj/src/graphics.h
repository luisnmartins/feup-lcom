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
#include "Bitmap.h"


//Bitmaps

typedef struct
{
 Bitmap *maca;
 Bitmap *body;
 Bitmap *body2;
 Bitmap *mouse;
 Bitmap *bg;
 Bitmap *bgmp;
 Bitmap *cabeca1hd;
 Bitmap *cabeca1he;
 Bitmap *cabeca1vc;
 Bitmap *cabeca1vb;
 Bitmap *cabeca2hd;
 Bitmap *cabeca2he;
 Bitmap *cabeca2vc;
 Bitmap *cabeca2vb;
 Bitmap *main_menu;
 Bitmap *mp_menu;
 Bitmap *cursor;
 Bitmap *numbers[11];
 Bitmap *sp_inst;
 Bitmap *kbc_inst;
 Bitmap *mokb_inst;
 Bitmap *pausesymb;
 Bitmap *bomb;
 Bitmap *explosion;
 Bitmap *wall;
 Bitmap *player1;
 Bitmap *player2;
 Bitmap *choose_main;
 Bitmap *choose_p1;
 Bitmap *choose_p2;
 Bitmap *counter1_delay;
 Bitmap *counter2_delay;
 Bitmap *counter3_delay;
 Bitmap *numbers_score[10];
 Bitmap *numbers_back;
}Bitmaps_struct;

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes  global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);
/**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit();

int update_matrix_snake(Snake *s1,int mouse);

int start_mode();


void clear_matrix();
void draw_screen(int mode);


void new_object_matrix(Snake *s1,unsigned int type);
void new_object_2_snakes_matrix(Snake *s1, Snake *s2, unsigned int type);
void remove_snakes_matrix();
int update_matrix_objects(Game_object *obj, Snake *s1);
int update_matrix_objects_2_snakes(Game_object *obj, Snake *s1, Snake *s2);
int update_matrix_snakemp(Snake *s1,Snake *s2,int *snake1_alive, int *snake2_alive);
void points_ingame_sp(Snake *s1); //pode ser metida no menu.c mas como e usado durante o jogo em si talvez tenha mais sentido deixar aqui
void points_ingame_mp (Snake *s1,Snake *s2);//a mesma ideia com points_ingame_sp
int verify_colision_walls_bgmap(int col,int row,int mode);
int add_fruit_matrix(int x, int y,Snake *s1);
int fruit_count();
int bomb_count();
void remove_bomb();
int add_bomb_matrix(int x, int y,Snake *s2);

Bitmaps_struct* getBM();

/**
 * @brief Print the 3, 2, 1 numbers used when a game is starting
 * @param number_delay Number to print (1, 2 or 3)
 */
void print_number_delay(int number_delay);



#endif /* __GRAPHICS_H */
