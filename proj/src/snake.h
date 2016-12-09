
#define SEG_HEIGHT 16
#define SEG_WIDTH 16
#define HORIZONTAL 0
#define VERTICAL 1
#define RIGHT_DOWN 0
#define LEFT_UP 1


#include <stdio.h>

typedef struct Segment{
	unsigned short row, col;
	struct Segment *next;
	struct Segment *before;
	unsigned short direction;
	unsigned short orientation;
}segment_t;


typedef struct {
	segment_t *head;
	segment_t *tail;
	unsigned int size;
	unsigned short boost;
}Snake;


void add_segment(Snake *s1,unsigned short row,unsigned short col);
Snake* new_snake(int size, unsigned short x, unsigned short y);
segment_t *new_seg(unsigned short col, unsigned short row);
