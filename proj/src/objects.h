
#define FRIENDLY_TYPE 0
#define DANGER_TYPE 1

#include <stdio.h>
typedef enum {
	FRUIT, OBSTACLE, SNAPCHAT // ADICONAR MAIS SE PRECISO
} object_name;

typedef struct {
	unsigned short row,col;
	int point_value,type;
	object_name name;

}Game_object;

Game_object *new_object(unsigned short row, unsigned short col,object_name name);
