#include "i8042.h"

#include <limits.h>
#include <string.h>
#include <errno.h>
#include "pixmap.h" // defines  pic1, pic2, etc



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
			"\t service run %s -args \"test_init <hexadecimal no. - mode> <decimal no. - delay>\"\n"
			"\t service run %s -args \"test_square<decimal no. - x>  <decimal no. - y> <decimal no. - size> <decimal no. - color>\"\n"
			"\t service run %s -args \"config\"\n"
			"\t service run %s -args \"gesture <decimal no. - length>\"\n",
			argv[0], argv[0], argv[0],argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short mode, delay, x, y, xf, yf, size, color, xpm, hor, delta, time;

	if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
		if (argc != 4) {
			printf("Graphics Card: wrong no. of arguments for test_init()\n");
			return 1;
		}
		mode = parse_ulong(argv[2], 16);
		delay = parse_ulong(argv[3], 10);
		/* Parses string to unsigned long */
		if (mode == ULONG_MAX || delay == ULONG_MAX)
			return 1;
		printf("test5::test_init(%lu, %lu)\n", mode, delay);

		return test_init(0x105, delay);
	}

	else if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
		if (argc != 6) {
			printf("Graphics Card: wrong no. of arguments for test_square()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		size = parse_ulong(argv[4], 10);
		color = parse_ulong(argv[5], 10);

	if (x == ULONG_MAX || y == ULONG_MAX|| size == ULONG_MAX || color == ULONG_MAX)
					return 1;
		printf("test5::test_square(%lu, %lu, %lu, %lu )", x, y, size, color);

		return test_square(x,y,size,color);
	}
	else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
		if (argc != 7) {
			printf("Graphics Card: wrong no of arguments for test_line()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		xf = parse_ulong(argv[4], 10);
		yf = parse_ulong(argv[5], 10);
		color = parse_ulong(argv[6], 10);


		printf("test5::test_line(%lu, %lu, %lu, %lu, %lu)\n", x, y, xf, yf, color);
		return test_line(x, y, xf, yf, color);
	}
	else if (strncmp(argv[1], "test_xpm", strlen("test_xpm")) == 0) {
		if (argc < 5) {
			printf("Graphics Card: wrong no. of arguments for test_xpm()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		const char* xpm = argv[4];

		if (x == ULONG_MAX || y == ULONG_MAX)
				return 1;

		if(strncmp(xpm, "pic1", strlen("pic1")) == 0)
				test_xpm(x,y,pic1);
		else if(strncmp(xpm, "pic2", strlen("pic2")) == 0)
			test_xpm(x,y,pic2);
		else if(strncmp(xpm, "pic3", strlen("pic3")) == 0)
					test_xpm(x,y,pic3);
		else if(strncmp(xpm, "cross", strlen("cross")) == 0)
					test_xpm(x,y,cross);
		else if(strncmp(xpm, "penguin", strlen("penguin")) == 0)
					test_xpm(x,y,penguin);
		else
			return 1;


		printf("test5::test_xpm(%lu, %lu, %lu)", x, y, xpm);

		return 0;
		/*else {
			printf("test5: %s - no valid function!\n", argv[1]);
			return 1;
		}*/

	}
	else if (strncmp(argv[1], "test_move", strlen("test_move")) == 0) {
		if (argc < 8)
		{
			printf("Graphics Card: wrong no of arguments for test_line()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		const char* xpm1 = argv[4];
		hor = parse_ulong(argv[5], 10);
		delta = parse_ulong(argv[6], 10);
		time = parse_ulong(argv[7], 10);

		if (x == ULONG_MAX || y == ULONG_MAX)
								return 1;

		if (strncmp(xpm1, "pic1", strlen("pic1")) == 0)
			test_move(x, y, pic1, hor, delta, time);
		else if (strncmp(xpm1, "pic2", strlen("pic2")) == 0)
			test_move(x, y, pic2, hor, delta, time);
		else if (strncmp(xpm1, "pic3", strlen("pic3")) == 0)
			test_move(x, y, pic3, hor, delta, time);
		else if (strncmp(xpm1, "cross", strlen("cross")) == 0)
			test_move(x, y, cross, hor, delta, time);
		else if (strncmp(xpm1, "penguin", strlen("penguin")) == 0)
			test_move(x, y, penguin, hor, delta, time);
		else
			return 1;


		printf("test5::test_line(%lu, %lu, %lu, %lu, %lu, %lu)\n", x, y, xpm, hor, delta, time);
		//return test_move(x, y, xpm, hor, delta, time);

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
