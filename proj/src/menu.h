

#include "graphics.h"
#include "constants.h"


/** @defgroup menu menu
 * @{
 *
 * Functions related to the game menus
 */
/**
 * @brief it fills the bmp global variable with the bitmaps loaded in graphics.c
 * */
void start_variables_menu();
/**
 * @brief it updates the x_pos_atual and y_pos_atual of the mouse
 * @param x deltax given by the mouse packet(at end x is given the value of the current position of mouse not deltax)
 * @param y deltay given by the mouse packet(at the end y is given the value of the current position of the mouse not deltay)
 * */
void update_pos_mouse(unsigned long *x, unsigned long *y);
/**
 * @brief draws in the screen the menu specified
 * @param mode to know what menu is going to draw, 0 for the main menu, 1 for the multiplayer menu
 * */
void draw_menu(int mode);
/**
 * @brief draws in the screen the mouse cursor in the current position of the mouse
 * */
void  update_menu_mouse();
/**
 * @brief it changes the bmp associated with the variable body
 * @param opt wich of the bodies is being chosen
 * */
void change_body(int opt);
/**
 * @brief it changes the bmp associated with the variable body2
 * @param opt which of the bodies as been chosen
 * */
void change_body2(int opt);
/**
 * @brief it changes all the bmps associated with the variables of the head of snake s1
 * @param opt which of the heads has been chosen in the choose the body menu
 * */
void change_head(int opt);
/**
 * @brief draws the menus to choose the body of the snakes
 * @param mode variabel to know which choose menu is going to draw, 1 for the menu that can change body and head of snake s1, 1 and 2 for menus to choose only the bodies of the snakes s1 and s2 respectively
 *
 * */
void draw_choose_snake(int mode);

/**
 * @brief draws in any of the choose menus a preview snake to see how the options chosen looks
 * @param snake_preview the snake it is going to draw and move
 * @param counter variable helpful to make sure if the snake is at the beggining or end of the demo
 * @param body_count variable helpful to make sure if the snake is at the beggining or end of the demo
 * */
void draw_preview_snake(Snake *snake_preview, int counter, int body_count);

/**
 * @brief it draws in the menus the current time of the system
 * @param hour the hour received by the rtc
 * @param min the minutes received by the rtc
 * @param seconds the seconds received by the rtc
 * */
void draw_time(int hour,int min, int seconds);
/**
 * @brief draws the game instructions of each game mode
 * @param mode to know which game mode it is, 1 for singleplayer 2 for 2 snakes and 3 for the snake and mouse mode (0 is to draw the pause message when game is paused)
 * */
void draw_instructions(int mode);
/**
 * @brief show the end game points of the snake(1 snake modes)
 * @param s1 snake that the points are checked
 * */
void show_points_sp(Snake *s1);
/**
 * @brief show the end game points of both players snakes (2 snake modes)
 * @param s1 snake of player 1 points
 * @param s2 snake of player 2 poitns
 * */
void show_points_mp(Snake *s1, Snake *s2);

