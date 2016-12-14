
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
	printf("end s1\n");
	return s1;

}

segment_t *new_seg(unsigned short col, unsigned short row)
{
	segment_snake *new_seg = (malloc(sizeof(segment_snake)));
	new_seg->seg.row = row;
	new_seg->seg.col = col;
	new_seg->seg.direction = HORIZONTAL;
	new_seg->seg.orientation = RIGHT_DOWN;
	new_seg->before = NULL;
	new_seg->next = NULL;

	return new_seg;

}


void add_segment(Snake *s1,unsigned short row,unsigned short col)
{
	printf("add segment\n");
	segment_snake *new_seg = (malloc(sizeof(segment_snake)));
	printf("alloc\n");
	new_seg->seg.row = row;
	new_seg->seg.col = col;
	new_seg->seg.direction = HORIZONTAL;
	new_seg->seg.orientation = RIGHT_DOWN;
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
		new_seg->before = s1->tail->seg;
		new_seg->next = NULL;
		s1->tail->next = new_seg->seg;
		s1->tail = new_seg;
	}
	s1->size++;
}


void move_snake(Snake* s1)
{
	segment_snake *s = s1->head;

	printf("ok continua bem\n");
	segment_snake *new_seg = (malloc(sizeof(segment_snake)));


	if(s->direction == HORIZONTAL)
	{


		printf("ok 15\n");
		new_seg->before = NULL;
		new_seg->next = s1->head->seg;
		new_seg->seg.direction = s1->head->seg.direction;
		new_seg->seg.orientation = s1->head->seg.orientation;
		new_seg->seg.col += s1->head->seg.orientation;

		s1->head->before = new_seg->seg;
		s1->head = new_seg;

		segment_snake *remove = s1->tail;

		segment_snake *to_subst_tail;
		to_subst_tail->seg.row = s1->tail->before->row;
		to_subst_tail->seg.col = s1->tail->before->col;
		to_subst_tail->seg.direction= s1->tail->before->direction;
		to_subst_tail->seg.orientation = s1->tail->before->orientation;
		 = s1->tail->before;
		//end_seg->row
		printf("cena\n");
		end_seg->col = s1->tail->before->col;
		end_seg->next = s1->tail->before->next;
		end_seg->before = s1->tail->before->before;

		end_seg->direction = s1->tail->before->direction;
		end_seg->orientation = s1->tail->before->orientation;
		free(s1->tail->before);

		s1->tail = end_seg;
		end_seg->before->next = end_seg;

		free(remove);
		s1->tail = end_seg;

		s1->tail->next = NULL;

		if(s1->head == NULL)
		{
			printf("merdou\n");
		}
		if(s1->tail == NULL)
		{
			printf("merdou rabo\n");
		}

	}
	if(s->direction == VERTICAL)
	{
			/*new_seg->before = NULL;
			new_seg->next = s1->head;
			new_seg->direction = s1->head->direction;
			new_seg->orientation = s1->head->orientation;
			new_seg->row += s1->head->orientation;
			s1->head->before = new_seg;
			s1->head = new_seg;
			remove = s1->tail;
			s1->tail = s1->tail->before;
			s1->tail->next = NULL;
			free(remove);*/

	}
}

