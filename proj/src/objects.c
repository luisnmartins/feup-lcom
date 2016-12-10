#include "objects.h"


Game_object *new_object(unsigned short row, unsigned short col,object_name name)
{
	Game_object *obj = (Game_object*)(malloc(sizeof(Game_object)));
	obj->row = row;
	obj->col = col;
	obj->name = name;
	switch(obj->name){
	case FRUIT:
		obj->type = FRIENDLY_TYPE;
		obj->point_value = 2;
		break;
	case SNAPCHAT:
		obj->type= FRIENDLY_TYPE;
		obj-> point_value = 4;
		break;
	case OBSTACLE:
		obj->type= DANGER_TYPE
		obj-> point_value = 0;
		break;
	default:
		break;
	}
}
