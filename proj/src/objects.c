#include "objects.h"


void new_object(Game_object *obj, object_name name)
{


	obj->row = rand()%64;
	obj->col = rand()%64;
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
		obj->type= DANGER_TYPE;
		obj-> point_value = 0;
		break;
	default:
		break;
	}
}

