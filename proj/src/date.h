#include "rtc.h"


/** @name rtc date */
/**@{
 *
 * Stored time values of the rtc
 */
///Represents the rtc date
typedef struct
{
	unsigned long hour;/**< @brief the hour*/
	unsigned long min;/**< @brief the minutes*/
	unsigned long sec;/**<@brief the seconds*/
	unsigned long day;/**<@brief the day of the year*/
	unsigned long month;/**<@brief the month of the year*/
	unsigned long year;/**< @brief the year*/
}date_rtc;
/** @} end of  rtc date*/
/**
 *
 * @brief Update the date struct pointer with the current hour
 *
 * @param date Pointer to an element of date_rtc type where the hour is setted
 */
void update_date(date_rtc *date);
