
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
	struct Segment *next;
	struct Segment *before;
}segment_snake;

typedef struct {
	segment_snake *head;
	segment_snake *tail;
	unsigned int size;
	unsigned short boost;
}Snake;


void add_segment(Snake *s1,unsigned short row,unsigned short col);
void new_snake(int size, unsigned short x, unsigned short y, Snake *s1);
segment_snake *new_seg(unsigned short col, unsigned short row);
void move_snake(Snake* s1);
