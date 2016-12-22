#include "rtc.h"

typedef struct
{
	unsigned short hour;
	unsigned short min;
	unsigned short sec;
	unsigned short day;
	unsigned short month;
	unsigned short year;
}date_rtc;

int update_date(date_rtc *date);
