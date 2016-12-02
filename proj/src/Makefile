COMPILER_TYPE= gnu
CC=gcc
PROG= proj
SRCS= main.c vbe.c video_gr.c timer.c keyboard.c read_xpm.c graphics.c bitmap.c
CCFLAGS= -Wall
DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys
LDFLAGS+= -L .
MAN=
BINDIR?= /usr/sbin
.include <bsd.prog.mk>
.include <bsd.gcc.mk>