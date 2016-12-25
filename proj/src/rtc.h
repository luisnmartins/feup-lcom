#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>

int can_read_date();

void set_binary();

int bcd_to_decimal(unsigned long number);

void read_date(unsigned long *day, unsigned long *month, unsigned long *year);

void read_time(unsigned long *hour, unsigned long *minute, unsigned long *sec);
