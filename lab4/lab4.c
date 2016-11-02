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
			"\t service run %s -args \"packet <decimal no.- compile_code>\"\n"
			"\t service run %s -args \"async <decimal no. - LEDarray>\"\n"
			"\t service run %s -args \"config <decimal no. - seconds>\"\n"
			"\t service run %s -args \"gesture <decimal no. - seconds>\"\n",
			argv[0], argv[0], argv[0],argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short compile_code, timed;
	unsigned short arraysize;
	unsigned short *ledarray;
	if (strncmp(argv[1], "packet", strlen("packet")) == 0) {
		if (argc != 3) {
			printf("Interrupt Handler: wrong no. of arguments for test_packet()\n");
			return 1;
		}
		compile_code = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (compile_code == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_scan(%lu)\n", compile_code);
		return kbd_test_scan(compile_code);
	}
	else if (strncmp(argv[1], "async", strlen("async")) == 0) {
		if (argc < 3) {
			printf("LED Array: wrong no. of arguments for test_async()\n");
			return 1;
		}
		ledarray = malloc(sizeof(unsigned short)*(argc-2));
		arraysize = argc-2;
		int i=0;
		for(i; i<arraysize; i++)
		{
			ledarray[i] = parse_ulong(argv[2+i], 10);
			if (*argv[2+i] == ULONG_MAX)
					return 1;
			 // Parses string to unsigned long
		}

		printf("test3::kbd_test_leds()");

		return kbd_test_leds(arraysize, ledarray);
	}
	else if (strncmp(argv[1], "config", strlen("config")) == 0) {
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

