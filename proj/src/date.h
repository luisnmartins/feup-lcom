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

/**
 *
 * @brief Update the date struct pointer with the current hour
 *
 * @param date Pointer to an element of date_rtc type where the hour is setted
 */
void update_date(date_rtc *date);
