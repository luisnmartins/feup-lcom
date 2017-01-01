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



/** @defgroup graphics graphics
 * @{
 *
 * Functions related to the graphics components of the game
 */

/** @name Graphics elements */
/**@{
 *
 * all bitmaps used in the game
 */
typedef struct
{
 Bitmap *maca;/**< @brief fruit eaten by the snake to grow*/
 Bitmap *body;/**< @brief body the s1 snake*/
 Bitmap *body2;/**< @brief body of the s2 snake*/
 Bitmap *game_over;/***<@brief game over message*/
 Bitmap *bg; /**< @brief map used in SP and Snake and Mouse mode */
 Bitmap *bgmp;/**< @brief map used in the mode with 2 snakes*/
 Bitmap *cabeca1hd;/**< @brief head of the s1 snake in the horizontal and positive directions*/
 Bitmap *cabeca1he;/**< @brief head of the s1 snake in the horizontal and negative directions*/
 Bitmap *cabeca1vc;/**< @brief head of the s1 snake in the vertical and negative directions*/
 Bitmap *cabeca1vb;/**< @brief head of the s1 snake in the vertical and positive directions*/
 Bitmap *cabeca2hd;/**< @brief head of the s2 snake in the horizontal and positive directions*/
 Bitmap *cabeca2he;/**< @brief head of the s2 snake in the horizontal and negative directions*/
 Bitmap *cabeca2vc;/**< @brief head of the s2 snake in the vertical and negative directions*/
 Bitmap *cabeca2vb;/**< @brief head of the s2 snake in the vertical and positive directions*/
 Bitmap *main_menu;/**< @brief menu that appears at the start of the game*/
 Bitmap *mp_menu;/** < @brief menu that appears when player selects multiplayer in main_menu*/
 Bitmap *cursor;/**< @brief mouse cursor*/
 Bitmap *numbers[11];/**< @brief all the numbers from 0 to 9 in order,and the char ':' and '/' used in time and final scores*/
 Bitmap *sp_inst;/**< @brief instructions of the singleplayer mode*/
 Bitmap *kbc_inst;/**< @brief instructions of the snake gladiator mode*/
 Bitmap *mokb_inst;/**< @brief instructions of the snake and mouse game mode*/
 Bitmap *pausesymb;/**< @brief pause message when the game is paused*/
 Bitmap *bomb;/**< @brief bomb that might kill a snake*/
 Bitmap *explosion;/**< @brief explosion if snake collides with a bomb*/
 Bitmap *press_enter; /**< @brief message press enter to continue at the end of each game*/
 Bitmap *player1;/**< @brief identifier of player 1*/
 Bitmap *player2;/**< @brief identifier of player 2*/
 Bitmap *choose_main;/**< @brief menu to choose the body and the head of the it wants to use(only in modes with one snake)*/
 Bitmap *choose_p1;/**< @brief menu in 2 snakes mode, to choose the body of the snake of player1 (snake s1)*/
 Bitmap *choose_p2;/**< @brief menu in 2 snakes mode, to choose the body of the snake of player2 (snake s2)*/
 Bitmap *counter1_delay;/**< @brief number 1 in the countdown before the start of each game*/
 Bitmap *counter2_delay;/**< @brief number 2 in the count down before the start of each game*/
 Bitmap *counter3_delay;/**< @brief number 3 in the count down before the start of each game*/
 Bitmap *numbers_score[10];/**< @brief numbers from 0 to 9 used to show the atual points of the snake ingame*/
 Bitmap *numbers_back;/**< @brief simple black background to put the numbers stated above, and to make a standard new wall that the snakes should'nt collide with*/
}Bitmaps_struct;
/** @} end of  graphics elements*/
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
/**
 * @brief updates the position of the snake in the screen and checks collisions
 * @param s1 snake that is going to be analised and update in the matrix
 * @param mouse flag to know if when a snake collides with a fruit (eats it) to know if a new fruit should be generated automatically,or if the game mode is snake and mouse and doesnt need to do it
 * @return 1 if the snake as collided with something other than a fruit, so we know the snake dies,return 0 if the snake is ok
 * */
int update_matrix_snake(Snake *s1,int mouse);
/**
 * @brief it call vg init to start the video mode in 11A and loads every bitmap used
 *
 * */
void start_mode();

/**
 * @brief it resets the graphics_matrix to all NULL pointers,so another game can be started
 * */
void clear_matrix();

/**
 * @brief it draws in the screen the current state of the game
 * @param flag to know what map is being used
 * */
void draw_screen(int mode);

/**
 *  @brief creates  a new object of type type and make sure its position in the matrix doesnt interfere with the snake
 *  @param s1 snake to compare positions wiht
 *  @param type what type of object it is (0 for fruit or 1 for bomb)
 * */
void new_object_matrix(Snake *s1,unsigned int type);
/**
 *  @brief creates  a new object of type type and make sure its position in the matrix doesnt interfere with the snakes
 * @param s1 snake to compare positions with
 * @param s2 second snake to compare positions with
 * @param type what type of object it is (0 for fruit or 1 for bomb)
 * */
void new_object_2_snakes_matrix(Snake *s1, Snake *s2, unsigned int type);

/**
 * @brief removes all snakes from the matrix
 * */
void remove_snakes_matrix();
/**
 * @brief places the new object created in the matrix making sure that is placed in a good spot
 * @param obj object that is being set
 * @param s1 snake to compare if it is placed on a good spot
 * @return 0 if has been successfully placed,1 otherwise
 * */
int update_matrix_objects(Game_object *obj, Snake *s1);
/**
 * @brief places the new object created in the matrix making sure that is placed in a good spot
 * @param obj object that is being set
 * @param s1 snake to compare if it is placed on a good spot
 * @param s2 second snake to compare if it is placed on a good spot
 * @return 0 if has been successfully placed,1 otherwise
 * */
int update_matrix_objects_2_snakes(Game_object *obj, Snake *s1, Snake *s2);
/**
 * @brief it updates the matrix for the game mode with 2 snakes (similar to update matrix snake)
 * @param s1 snake of player 1 that is being updated in the matrix
 * @param s2 snake of player 2 that is being updated in the matrix
 * @param snake1_alive flag to know the living state of snake1 (so the game doesnt end when one of the snakes dies)
 * @param snake2_alive flag  to know the living state of snake2
 * @return 1 if any of the snakes has collided with a dangerous object,otherwise returns 0
 * */
int update_matrix_snakemp(Snake *s1,Snake *s2,int *snake1_alive, int *snake2_alive);
/**
 * @brief show the points that the snake currently has during a game (game mode with only one snake)
 * @param s1 snake to check its points
 * */
void points_ingame_sp(Snake *s1);
/**
 * @brief shwo the points that both snakes has in real time during a game(game mode with 2 snakes)
 * @param s1 snake to check points of player 1
 * @param s2 snake to check points of player 2
 * */
void points_ingame_mp (Snake *s1,Snake *s2);

/**
 * @brief checks if specific place in the screen is valid(if it is not the wall of the maps used)
 * @param col column that is going to be studied
 * @param row row that is being studied
 * @param mode to check what map we are checking collisions, 1 for map with only one snake , 2 for the other map
 * @return 1 if it is an invalid place(if it is in a same position with a wall of the map), 0 otherwise
 * */
int verify_colision_walls_bgmap(int col,int row,int mode);
/**
 * @brief adds an object of type fruit in the position given, places only if it is valid spot (used in the mouse game mode)
 * @param x position on x axis of the mouse
 * @param y position on y axis of the mouse
 * @param s1 snake to validate spot to put
 * @return 0 if the fruit has been succesfully added to the matrix, 1 otherwise
 * */
int add_fruit_matrix(int x, int y,Snake *s1);
/**
 * @brief counts how many fruits are in the matrix
 * @return the number of fruits in the matrix
 * */
int fruit_count();
/**
 * @brief count how many bombs are in the matrix
 * @return the number of bombs in the matrix
 * */
int bomb_count();
/**
 * @brief removes from the matrix the first bomb it encounters
 * */
void remove_bomb();
/**
 * @brief adds an object of type bomb in the position given,places only if it is a valid spot(used in mouse game mode)
 * @param x position on the x axis of the mouse
 * @param y position on the y axis of the mouse
 * @param s1 snake to validate spot to put matrix
 * ¶eturn 0 if the bomb has been successfuly added to the matrix, 1 otherwise
 * */
int add_bomb_matrix(int x, int y,Snake *s1);

/**
 * @brief gets the bitmap_struct with all bitmaps used in the project
 * @return the bmp global variable
 * */
Bitmaps_struct* getBM();

/**
 * @brief Print the 3, 2, 1 numbers used when a game is starting
 * @param number_delay Number to print (1, 2 or 3)
 */
void print_number_delay(int number_delay);



#endif /* __GRAPHICS_H */
