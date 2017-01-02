#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>


/** @defgroup rtc rtc
 * @{
 *
 * Functions related to the rtc
 */
/**
 * @brief simple function that sees if the date can be read
 * @returns 1 if it cannot be read 0 otherwise
 * */
int can_read_date();

/**
 *  @brief verify if real time clock is on binary mode
 *  @return return 1 if is on bcd mode and 0 if is on binary mode
 */
int is_binary();

/**
 * @brief it "transforms" a binary number to a decimal one
 * @param number in binary that is going to change to decimal
 * @return the decimal number got
 * */
int bcd_to_decimal(unsigned long number);
/**
 * @brief reads the right registers of the rtc to get the date of the system
 * @param day variable where the day read is going to be stored
 * @param month variable where the month read is going to be stored
 * @param year variable where the  year read is going to be stored
 * */
void read_date(unsigned long *day, unsigned long *month, unsigned long *year);
/**
 * @brief reads the necessary registers of the rtc to get the time of the system
 * @param hour variable where the hour is going to be stored
 * @param minute variable where the minutes are going to be stored
 * @param sec variable where the seconds are going to be stored
 * */
void read_time(unsigned long *hour, unsigned long *minute, unsigned long *sec);
