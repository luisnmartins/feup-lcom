
#define SEG_HEIGHT 16
#define SEG_WIDTH 16
#define HORIZONTAL 0
#define VERTICAL 1
#define RIGHT_DOWN 1
#define LEFT_UP -1


#include <stdio.h>


/** @defgroup snake snake
 * @{
 *
 * Functions associated with the creation of the snake and its movements
 */
/** @name Snake */
/**@{
 *
 * Snake using a linked list
 */
typedef struct Segment{
	unsigned short row, col; /**< @brief position in the matrix_graphics*/
	unsigned short direction;/**< @brief direction it is facing, vertical or horizontal*/
	unsigned short orientation;/** <@brief orientation it is facing. if its moving in positive direction or negative*/
	struct Segment *next; /** <@brief pointer to the next body part(like a linked list)*/
	struct Segment *before;/** <@brief pointer to the previous body part*/
}segment_snake;

typedef struct {
	segment_snake *head; /**< @brief pointer to the head of the snake*/
	segment_snake *tail; /** <@brief pointer to the tail of the snake*/
	unsigned int size; /** <@brief size of the snake(number of segment_snake)*/
	unsigned short velocity;/** <@brief velocity the snake is moving*/
	unsigned short boost;/** <@brief flag to know if the snake is boosting*/
	unsigned short boost_time; /** <@brief the amount of time the snake can boost */
}Snake;

/** @} end of  Snake*/


/**
 * @brief adds a new segment_snake to the snake as the new head of the snake
 * @param s1 snake which the new segment is going to be added
 * @param row member row of the new segment
 * @param col member col of the new segment
 *
 * The last elements of the new segment, are based on the segments of the snake(especially the head)
 * */
void add_segment(Snake *s1,unsigned short row,unsigned short col);
/**
 * @brief creates a new snake
 * @param size number of segments the snake is going to have(add_segment is used for this)
 * @param x the row member of all segments of the new snake
 * @param y the col member of all segments of the new snake
 * @param s1 the variable where the snake is going to be saved
 * Every new snake and its segments have the direction(horizontal) and oriectation(positive) as default
 * */
void new_snake(int size, unsigned short x, unsigned short y, Snake *s1);
/**
 * @brief moves the snake by one position based on its segments direction and orientation
 * @param s1 snake that is going to be moved
 *
 * Basically it moves by just removing the tail of the snake and create and put a new head
 * */
void move_snake(Snake* s1);
/**
 * @brief sets the boost flag and doubles the snake velocity
 * @param s1 snake that is going to be set
 * */
void set_boost(Snake* s1);
/**
 * @brief resets the boost flag and decreases the snake velocity
 * @param s1 snake that is going to be reset
 *
 * It is basically the opposite of set_boost
 * */
void stop_boost(Snake *s1);
/**
 * @brief  resets the snake that is used in the menu preview(when choosing the snake skin)
 * @param snake snake that is going to be reset
 * @param col column that is going to be reset to
 * */
void set_snake(Snake* snake, int col);
/**
 * @brief increases the size of the snake by adding a new segment as the tail of the snake
 * @param s1 snake which is going to increase
 *
 * It is used when the snake eats a fruit, it is basically add_segment but a little more restrictive
 * */
void inc_snake(Snake *s1);
