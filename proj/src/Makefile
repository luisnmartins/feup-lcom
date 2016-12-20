COMPILER_TYPE= gnu
CC=gcc
PROG= proj
SRCS= snake.c Bitmap.c main.c vbe.c video_gr.c timer.c keyboard.c read_xpm.c graphics.c man_events.c objects.c mouse.c
CCFLAGS= -Wall
DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys
LDFLAGS+= -L .
MAN=
BINDIR?= /usr/sbin
.include <bsd.prog.mk>
.include <bsd.gcc.mk>