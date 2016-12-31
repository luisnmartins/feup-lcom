
#define FRIENDLY_TYPE 0
#define DANGER_TYPE 1

#include <stdio.h>


/** @name object_name */
/**@{
 *
 * Name associations to a specific object
 */

typedef enum {
	FRUIT, BOMB //add more if it's necessary
} object_name;

/** @} end of  object_name*/

/** @name Game object */
/**@{
 *
 * Objects used in game
 */
typedef struct {
	unsigned short row,col; /**< @brief position in the matrix_graphics*/
	int point_value; /** <@brief how many points the object is valued (UNUSED)*/
	object_name name; /**< @brief name of the object of type object_name*/

}Game_object;
/** @} end of  Game_object*/

/**
 * @brief it creates a new object in a random position
 * @param obj object that is going to be built
 * @param name name of the object to know what type it is
 * */
void new_object(Game_object *obj, object_name name);
