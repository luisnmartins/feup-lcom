#include "test3.h"
#include "i8042.h"

#include <limits.h>
#include <string.h>
#include <errno.h>
#include "keyboard.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	/* DO NOT FORGET TO initialize service */
	sef_startup();
	sys_enable_iop(SELF);

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"scan <decimal no.- compile_code>\"\n"
			"\t service run %s -args \"led <decimal no. - LEDarray>\"\n"
			"\t service run %s -args \"timed <decimal no. - seconds>\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short compile_code, timed;
	unsigned short arraysize;
	unsigned short *ledarray;
	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if (argc != 3) {
			printf("Interrupt Handler: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		compile_code = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (compile_code == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_scan(%lu)\n", compile_code);
		return kbd_test_scan(compile_code);
	}
	else if (strncmp(argv[1], "led", strlen("led")) == 0) {
		if (argc != 3) {
			printf("LED Array: wrong no. of arguments for kbd_test_leds()\n");
			return 1;
		}
		ledarray = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (ledarray == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_leds(%su, %su)\n", arraysize, ledarray);
		//return kbd_test_leds(arraysize, ledarray);
	}
	else if (strncmp(argv[1], "timed", strlen("timed")) == 0) {
		if (argc != 3) {
			printf("timer: wrong no of arguments for timer_test_int()\n");
			return 1;
		}
		timed = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (timed == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_timed_scan(%lu)\n", timed);
		return kbd_test_timed_scan(timed);
	}
	else {
		printf("test3: %s - no valid function!\n", argv[1]);
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
