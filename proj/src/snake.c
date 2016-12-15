
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

	segment_snake* remove = s1->tail;
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
		//printf("COL2: %d\n", col);
			//		printf("ROW2: %d\n", row);
		//printf("INIT: %d \n", col);		//s1->tail = s1->tail->before;
		//free(remove);



	}
	if(s1->head->direction == VERTICAL)
	{
		/*printf("hgjesrkgjm\n");
				printf("okdf\n");
		new_seg->before = NULL;
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

