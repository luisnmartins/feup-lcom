
#define SEG_HEIGHT 16
#define SEG_WIDTH 16
#define HORIZONTAL 0
#define VERTICAL 1
#define RIGHT_DOWN 1
#define LEFT_UP -1


#include <stdio.h>

typedef struct Segment{
	unsigned short row, col;
	unsigned short direction;
	unsigned short orientation;
}segment_t;

typedef struct Segment2
{
	segment_t seg;
	segment_t* next;
	segment_t* before;
}segment_snake;

typedef struct {
	segment_snake *head;
	segment_snake *tail;
	unsigned int size;
	unsigned short boost;
}Snake;


void add_segment(Snake *s1,unsigned short row,unsigned short col);
Snake* new_snake(int size, unsigned short x, unsigned short y);
segment_t *new_seg(unsigned short col, unsigned short row);
void move_snake(Snake* s1);
