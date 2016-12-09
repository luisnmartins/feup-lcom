
#define SEG_HEIGHT 16
#define SEG_WIDTH 16

#include <stdio.h>


typedef struct Segment Segment;

struct Segment{
	unsigned short row, col;
	Segment *next;
	Segment *before;
	unsigned short direction;
	unsigned short orientation;
};


typedef struct {
	Segment *head;
	Segment *tail;
	unsigned int size;
	unsigned short boost;
}Snake;

Snake* new_snake(int size, unsigned short x, unsigned short y);
