CC = g++
CFLAGS = -I./ -g -O2 -D_REENTRANT -Wall

CLEANFILES = core core.* *.core *.o temp.* *.out typescript* *.lc *.lh *.bsdi *.sparc *.uw


main:   main.cpp draw.cpp chess.cpp
		${CC} ${CFLAGS} $^ -o $@


clean:
		rm -f ${PROGS} ${CLEANFILES}

