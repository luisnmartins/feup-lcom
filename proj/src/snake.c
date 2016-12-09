
#include "snake.h"

Snake* new_snake(int size, unsigned short row, unsigned short col)
{

	Snake *s1 = (Snake*)(malloc(sizeof(Snake)));
	s1->size=0;
	s1->boost = 0;

	int i=0;
	for(i; i<size; i++)
	{
		add_segment(&s1, row, col);
		col++;
	}
	return s1;

}

void add_segment(Snake *s1,unsigned short row,unsigned short col)
{
	Segment *new_seg = (Segment*)(malloc(sizeof(Segment)));
	new_seg->row = row;
	new_seg->col = col;
	if(s1->head == NULL)
	{
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
