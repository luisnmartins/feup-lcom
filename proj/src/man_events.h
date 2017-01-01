#ifndef __MAN_EVENTS_H
#define __MAN_EVENTS_H

#include "menu.h"



/** @defgroup man_events man_events
 * @{
 *
 * Functions to interpret what to do with the interrupts of the timer,keyboard and mouse (main game state machine)
 */
/**
 * time
 of the system
 * */
date_rtc date;

/**
 * Snake created used for all game modes
 * */
static Snake *s1;
/**
 * Snake created used for all the multiplayer modes
 * */
static Snake *s2;
/**
 * Snake created to preview the chosen in the choose the body of the snake menu before every game
 * */
static Snake *s_preview;
/**
 * Flag to know if snake s1 as collided with something(wall or bomb)
 * */
static int flag_colision = 0;
/**
 * Flag to know if snake s2 as collided with something(wall or bomb)
 * */
static int flag_colision2 = 0;
/**
 * Global counter to set 3 seconds before every game starts
 * */
static int number_delay=3;
static int snakes_mp_modify =0;
/**
 * Flag to know if buffer is full
 * */
static int buf_full =0;
/**
 * Flag to know if a body has been chosen in the choose the body menu before each game
 * */
static int body_flag = 0;
/**
 * Flag used in multiplayer with 2 snakes to know wich snake is being changed in the choose the body menu
 * */
static int choose = 0;
/**
 * Variable to make sure that in the 2 snakes mode, the same body isnt chosen for both snakes
 * */
static int choose1 = 0;
/**
 * Flag to know if a head has been chosen in the choose the body menu before each game
 * */
static int head_flag = 0;
/**
 * Flag to know if it has to make the second round of the multiplayer with mouse mode
 * */
static int second_snake = 0;

/** @name state machine */
/**@{
 *
 * States of the state machine
 */
typedef enum {
	MENU_T, SP_T,WAIT_T, MPMENU_T, MOKB_T ,KBC_T, EXIT_T, END_T, PAUSE_T,CHOOSE_SN_T,START_DELAY_T
} states;
/** @} end of  state machine*/

/** @name state machine ev */
/**@{
 *
 * events of the state machine
 */
typedef enum {
	OPT_SP, OPT_MP,OPT_KBC,OPT_MOKB, OPT_EXIT, COLISION, START_E ,ESC_PRESSED,DELAY_E
} event;
/** @} end of  state machine ev*/
static states p=MENU_T;
 event t;
/**
 * @brief main game state machine that knows and interprets the state the game is
 * @param st state that the dfa is currently in
 * @param ev event that may possibly enable the trasition to another state
 * */
void check_game_status(states *st, event *ev);

/**
 * @brief it interprets the interrupts of the keyboard and "acts" if the keys are pressed in the necessary states
 * @param out_buf the code of the key pressed (it works with codes of 2 Bytes)
 * */
int keyboard_event_handler(unsigned long out_buf);
/**
 * @brief it interprets the interrupts of the timer and acts differently depending of the state that the state machine is currently in
 * @param counter of the interrupt handler
 * */
int timer_event_handler(unsigned short counter);
/**
 * @brief in interprets the interrupts of the mouse and acts depending of the currently state of the state machine
 * @param packet_mouse the mouse packet that is useful to know the position of the mouse and the buttons that are pressed
 * */
void mouse_event_handler(unsigned long *packet_mouse);
/**
 * @brief it makes the necessary actions to start a game mode (established by the parameter), create snake(s), put them in the matrix,add the initial objects,etc
 * @param mode simple number to identify the game mode that is going to start
 *
 *If mode is equal to 1 the function is going to make the preparations to the singleplayer mode
 *If mode is equal to 2 the function is going to make the preparations to the multiplayer, 2 snakes mode
 *If mode is equal to 3 the function is going to make the preparations to the multiplayer with mouse mode
 * */
void game_start(int mode);
/**
 * @brief creates the snake that is shown in the choose skin of the snake menu before each game
 * */
void new_snake_preview();










#endif /* __MAN_EVENTS_H */
