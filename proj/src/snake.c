
#include "snake.h"

int new_snake(int size, unsigned short line, unsigned short col)
{

	int i=1;
	segment seg1;
	seg1.line = line;
	seg1.col = col;
	seg1.before = NULL;
	seg1.next = NULL;
	seg1.direction = 0;
	snake s1;
	s1.head = &seg1;
	s1.tail = &seg1;
	s1.size = 1;
	s1.boost =0;
	for(i; i<size; i++)
	{
		segment seg2;
		seg2.line = line;
		seg2.col = s1.tail->col++;
		seg2.direction= 0;
		add_segment(&s1, &seg2);
	}


}

void add_segment(snake *s1, segment *seg1)
{
	/*seg1->before = s1->tail;
	seg1->next = NULL;
	s1->tail = seg1;
	s1->size++;
*/

}
