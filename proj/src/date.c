#include "date.h"

void update_date(date_rtc *date){


	int flag = 1;
	//set_binary();
	do
	{
		if(can_read_date() == 0)
		{

			read_date(&(date->day), &(date->month), &(date->year));
			read_time(&(date->hour), &(date->min), &(date->sec));
			flag = 0;
		}
	}while(flag == 1);


}
