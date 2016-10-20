#include "test3.h"
#include "i8254.h"
#include <limits.h>
#include <string.h>
#include <errno.h>

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	/* DO NOT FORGET TO initialize service */
	sef_startup();

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"scan <decimal no.- IH>\"\n"
			"\t service run %s -args \"led <decimal no. - LEDarray>\"\n"
			"\t service run %s -args \"timed <decimal no. - seconds>\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long ih, ledarray, timed;
	if (strncmp(argv[1], "IH", strlen("IH")) == 0) {
		if (argc != 3) {
			printf("Interrupt Handler: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		ih = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (ih == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_scan(%lu)\n", ih);
		return kbd_test_scan(ih);
	}
	else if (strncmp(argv[1], "LEDarray", strlen("LEDarray")) == 0) {
		if (argc != 3) {
			printf("LED Array: wrong no. of arguments for kbd_test_led()\n");
			return 1;
		}
		ledarray = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (ledarray == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_led(%lu)\n", ledarray);
		return kbd_test_led(ledarray);
	}
	else if (strncmp(argv[1], "int", strlen("int")) == 0) {
		if (argc != 3) {
			printf("timer: wrong no of arguments for timer_test_int()\n");
			return 1;
		}
		time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (time == ULONG_MAX)
			return 1;
		printf("timer::timer_test_int(%lu)\n", time);
		return timer_test_int(time);
	}
	else {
		printf("timer: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
