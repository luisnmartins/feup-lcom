

typedef enum {
	MENU, SP, MP, MOKB ,KBC1, EXIT
} states;
typedef enum {
	OPT1,OPT2,OPT3 //mais cenas
} event;


void check_game_status(states *st, event *ev)

{
	switch(*st){
	case MENU:
		if(*ev == OPT1)
			*st = SP;
		else if (*ev == OPT2)
			*st = MP;
		else if (*ev == OPT3)
			*st = EXIT;
		break;
	case EXIT:
		//sai do programa
		break;
	case SP:
		//TODO
		break;
	case MP:
		if(*ev == OPT1)
			*st = KBC1;
		else if (*ev == OPT2)
			*st = MOKB;
		break;

	}

}

void keyboard_event_handler(unsigned long out_buf)
{

	if(out_buf & 0xFF00 == 0xE0)
	{

	}
}

void timer_event_handler(unsigned short counter)
{
	//TODO if(single_p state) {gera ecra e cobra, continue, espera pelo clique da tecla para)

}
