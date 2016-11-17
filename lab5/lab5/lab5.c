#include "i8042.h"
#include "mouse.h"

#include <limits.h>
#include <string.h>
#include <errno.h>


static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
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
			"\t service run %s -args \"test_init <decimal no. - mode> <decimal no. - delay>\"\n"
			"\t service run %s -args \"async <decimal no. - x>  <decimal no. - y> <decimal no. - size> <decimal no. - color>\"\n"
			"\t service run %s -args \"config\"\n"
			"\t service run %s -args \"gesture <decimal no. - length>\"\n",
			argv[0], argv[0], argv[0],argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short np, time, leng;

	if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
		if (argc != 3) {
			printf("Interrupt Handler: wrong no. of arguments for test_packet()\n");
			return 1;
		}
		np = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (np == ULONG_MAX)
			return 1;
		printf("test4::test_packet(%lu)\n", np);

		return test_packet(np);
	}
	else if (strncmp(argv[1], "async", strlen("async")) == 0) {
		if (argc < 3) {
			printf("LED Array: wrong no. of arguments for test_async()\n");
			return 1;
		}
		time = parse_ulong(argv[2], 10);
		if (time == ULONG_MAX)
					return 1;
		printf("test4::test_async(%lu)", time);

		return test_async(time);
	}
	else if (strncmp(argv[1], "config", strlen("config")) == 0) {
		/*if (argc != 3) {
			printf("Conf: wrong no of arguments for test_config()\n");
			return 1;
		}*/
		printf("test4::test_config()\n");
		return test_config();
	}
	else if (strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
		if (argc < 3) {
			printf("MOUSE: wrong no. of arguments for test_gesture()\n");
			return 1;
		}
		leng = parse_long(argv[2], 10);
		if (leng == LONG_MAX)
					return 1;
		printf("test4::test_gesture(%ld)", leng);

		return test_gesture(leng);
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

static long parse_long(char *str, int base)
{
		char *endptr;
		unsigned long val;

		/* Convert string to unsigned long */
		val = strtoul(str, &endptr, base);

		/* Check for conversion errors */
		if ((errno == ERANGE && val == LONG_MAX) || (errno != 0 && val == 0)) {
			perror("strtoul");
			return LONG_MAX;
		}

		if (endptr == str) {
			printf("timer: parse_ulong: no digits were found in %s\n", str);
			return LONG_MAX;
		}

		/* Successful conversion */
		return val;
}
