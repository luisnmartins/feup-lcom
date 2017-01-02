#include "rtc.h"
#include "constants.h"

//adapted from slides code
int can_read_date() {
	unsigned long regA = 0;

	sys_outb(RTC_ADDR_REG, RTC_REG_A);
	sys_inb(RTC_DATA_REG, &regA);
	if ((regA & RTC_UIP) != 0)
		return 1;
	else
		return 0;

}

int is_binary() {
	unsigned long regB = 0;

	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	sys_inb(RTC_DATA_REG, &regB);
	if ((regB & BINARY_MODE) != 0)
		return 1;
	else
		return 0;

}

int bcd_to_decimal(unsigned long number) {
	return ((number & 0xF0) >> 4) * 10 + (number & 0x0F);
}

void read_date(unsigned long *day, unsigned long *month, unsigned long *year) {

	sys_outb(RTC_ADDR_REG, RTC_DAY_REG);
	sys_inb(RTC_DATA_REG, day);
	sys_outb(RTC_ADDR_REG, RTC_MON_REG);
	sys_inb(RTC_DATA_REG, month);
	sys_outb(RTC_ADDR_REG, RTC_YEAR_REG);
	sys_inb(RTC_DATA_REG, year);
}

void read_time(unsigned long *hour, unsigned long *minute, unsigned long *sec) {

	sys_outb(RTC_ADDR_REG, RTC_H_REG);
	sys_inb(RTC_DATA_REG, hour);
	sys_outb(RTC_ADDR_REG, RTC_MIN_REG);
	sys_inb(RTC_DATA_REG, minute);
	sys_outb(RTC_ADDR_REG, RTC_SEC_REG);
	sys_inb(RTC_DATA_REG, sec);
}
