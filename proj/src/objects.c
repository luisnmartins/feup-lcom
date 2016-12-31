#include "objects.h"


void new_object(Game_object *obj, object_name name)
{


	obj->row = rand()%64;
	obj->col = rand()%64;
	obj->name = name;
	switch(obj->name){
	case FRUIT:
		obj->point_value = 2;
		break;
	case BOMB:
		obj-> point_value = 0;
		break;
	default:
		break;
	}
}

