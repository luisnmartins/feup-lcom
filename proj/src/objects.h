
#define FRIENDLY_TYPE 0
#define DANGER_TYPE 1

#include <stdio.h>
#include "Bitmap.h"

typedef enum {
	FRUIT, OBSTACLE, SNAPCHAT //add more if it's necessary
} object_name;

typedef struct {
	unsigned short row,col;
	int point_value,type;
	object_name name;

}Game_object;

void new_object(Game_object *obj, object_name name);
