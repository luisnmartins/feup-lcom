
#include "snake.h"

void new_snake(int size, unsigned short row, unsigned short col, Snake* s1)
{
	printf("new_snake\n");

	s1->size=0;
	s1->boost = 0;
	s1->head = NULL;
	int i=0;
	int coluna = col;
	while(i<size)
	{
		add_segment(s1, row, coluna);
		//printf("%d\n", col);
		//printf("row: %d\n", row);
		coluna++;
		i++;
	}
	i=0;
	segment_snake *seg1 = s1->tail;
	while(i<size)
	{
		printf("COLUNA: %d\n", seg1->col);
		printf("LINHA: %d\n", seg1->row);
		seg1 = seg1->before;
				i++;
	}
	printf("end s1\n");


}

/*segment_snake *new_seg(unsigned short col, unsigned short row)
{
	segment_snake *new_seg = NULL;
	new_seg = (malloc(sizeof(segment_snake)));
	new_seg->row = row;
	new_seg->col = col;
	new_seg->direction = HORIZONTAL;
	new_seg->orientation = RIGHT_DOWN;
	new_seg->before = NULL;
	new_seg->next = NULL;

	return new_seg;

}*/

void inc_snake(Snake *s1)
{
	segment_snake* new_seg = NULL;
	new_seg = malloc(sizeof(segment_snake));
	int inc = s1->tail->orientation;
	int dir = s1->tail->direction;
	if(dir == HORIZONTAL)
	{

		new_seg->row = s1->tail->row;
		new_seg->col = s1->tail->col-inc;
		new_seg->direction = HORIZONTAL;
		new_seg->orientation = s1->tail->orientation;
		new_seg->next = NULL;
		new_seg->before = s1->tail;
		s1->tail->next = new_seg;
		s1->tail = new_seg;
	}
	else if(dir == VERTICAL)
	{

		new_seg->row = s1->tail->row - inc;
		new_seg->col = s1->tail->col;
		new_seg->direction = HORIZONTAL;
		new_seg->orientation = s1->tail->orientation;
		new_seg->next = NULL;
		new_seg->before = s1->tail;
		s1->tail->next = new_seg;
		s1->tail = new_seg;
	}
	s1->size++;
}



void add_segment(Snake *s1,unsigned short row,unsigned short col)
{

	if(s1->head == NULL)
	{
		segment_snake* new_seg = NULL;
		new_seg = malloc(sizeof(segment_snake));
		if(new_seg == NULL)
		{

			return;
		}

		new_seg->row = row;
		new_seg->col = col;
		new_seg->direction = HORIZONTAL;
		new_seg->orientation = RIGHT_DOWN;
		new_seg->before = NULL;
		new_seg->next = NULL;
		s1->head = new_seg;
		s1->tail = new_seg;
	}
	else
	{
		segment_snake* new_seg = NULL;
		new_seg = malloc(sizeof(segment_snake));
		//printf("cola: %d\n", col);
		new_seg->row = row;
		new_seg->col = col;
		new_seg->direction = s1->head->direction;
		new_seg->orientation = s1->head->orientation;
		new_seg->next = s1->head;
		new_seg->before = NULL;
		s1->head->before = new_seg;
		s1->head = new_seg;

	}
	//printf("TAILR: %d\n", s1->tail->row);
	//printf("TAILC: %d\n", s1->tail->col);
	s1->size++;
}


void move_snake(Snake* s1)
{



	segment_snake* new_seg = NULL;
	new_seg = malloc(sizeof(segment_snake));

	//segment_snake* remove = s1->tail;
	int inc = s1->head->orientation;
	printf("INC: %d\n", inc);
	int row = s1->head->row;
	int col = s1->head->col;
	if(s1->head->direction == HORIZONTAL)
	{
		printf("COL: %d\n", col);
		printf("ROW: %d\n", row);

		col += inc;
		add_segment(s1,row, col);
		s1->size--;

		s1->tail = s1->tail->before;

		free(s1->tail->next);
		s1->tail->next= NULL;
		printf("Col do tail novo: %d\n", s1->tail->col);

		/*new_seg = s1->head;
		while (new_seg->next->next != NULL) {
	        new_seg = new_seg->next;
		}
		free(new_seg->next);
		new_seg->next = NULL;
		s1->tail = new_seg;*/

		//printf("COL2: %d\n", col);
			//		printf("ROW2: %d\n", row);
		//printf("INIT: %d \n", col);		//s1->tail = s1->tail->before;
		//free(remove);



	}else
	if(s1->head->direction == VERTICAL)
	{

				row += inc;
				add_segment(s1,row, col);
				s1->size--;
				printf("row: %d\n",row);
				printf("col: %d\n",col);

				s1->tail = s1->tail->before;

				free(s1->tail->next);
				s1->tail->next= NULL;
				printf("Col do tail novo: %d\n", s1->tail->col);


	}
}

