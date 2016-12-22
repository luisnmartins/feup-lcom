#include "date.h"

void update_date(date_rtc *date){
	int flag = 1;

	if(can_read_date() == 0)
	{
		read_date(&(date->day), &(date->month), &(date->year));

	}


}
