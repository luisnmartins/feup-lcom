#include "rtc.h"

typedef struct
{
	unsigned long hour;
	unsigned long min;
	unsigned long sec;
	unsigned long day;
	unsigned long month;
	unsigned long year;
}date_rtc;

void update_date(date_rtc *date);
