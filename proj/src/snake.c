
#include "snake.h"

Snake* new_snake(int size, unsigned short row, unsigned short col)
{
	printf("new_snake\n");
	Snake *s1 = (Snake*)(malloc(sizeof(Snake)));
	s1->size=0;
	s1->boost = 0;
	s1->head = NULL;
	int i=0;
	for(i; i<size; i++)
	{
		add_segment(s1, row, col);
		col++;
	}
	return s1;

}

segment_t *new_seg(unsigned short col, unsigned short row)
{
	segment_t *new_seg = (malloc(sizeof(segment_t)));
	new_seg->row = row;
	new_seg->col = col;
	new_seg->direction = HORIZONTAL;
	new_seg->orientation = RIGHT_DOWN;
	new_seg->before = NULL;
	new_seg->next = NULL;

	return new_seg;

}


void add_segment(Snake *s1,unsigned short row,unsigned short col)
{
	printf("add segment\n");
	segment_t *new_seg = (malloc(sizeof(segment_t)));
	printf("alloc\n");
	new_seg->row = row;
	new_seg->col = col;
	new_seg->direction = HORIZONTAL;
	new_seg->orientation = RIGHT_DOWN;
	if(s1->head == NULL)
	{
		printf("esta no if");
		new_seg->before = NULL;
		new_seg->next = NULL;
		s1->head = new_seg;
		s1->tail = new_seg;
	}
	else
	{
		new_seg->before = s1->tail;
		new_seg->next = NULL;
		s1->tail->next = new_seg;
		s1->tail = new_seg;
	}
	s1->size++;
}
