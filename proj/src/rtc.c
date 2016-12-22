
//adapted from slides code
int can_read_date()
{
	unsigned long regA = 0;

	sys_outb(RTC_ADDR_REG, RTC_REG_A);
	sys_inb(RTC_DATA_REG, &regA);
	if((regA & RTC_UIP) != 0)
		return 1;
	else
		return 0;

}

void read_date(unsigned short *day, unsigned short *month, unsigned short *year)
{
	sys_outb(RTC_ADDR_REG, RTC_DAY_REG);
	sys_inb(RTC_DATA_REG, &day);
	sys_outb(RTC_ADDR_REG, RTC_MON_REG);
	sys_inb(RTC_DATA_REG, &month);
	sys_outb(RTC_ADDR_REG, RTC_YEAR_REG);
	sys_inb(RTC_DATA_REG, &year);
}

void read_time(unsigned short *hour, unsigned short *minute, unsigned short *sec)
{
	sys_outb(RTC_ADDR_REG, RTC_H_REG);
		sys_inb(RTC_DATA_REG, &hour);
		sys_outb(RTC_ADDR_REG, RTC_MIN_REG);
		sys_inb(RTC_DATA_REG, &minute);
		sys_outb(RTC_ADDR_REG, RTC_SEC_REG);
		sys_inb(RTC_DATA_REG, &sec);
}
