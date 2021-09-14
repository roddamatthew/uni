PROJECT=bb
SRCS=bb.c rsa.c oracle.c main.c
OBJS=${SRCS:.c=.o}

CFLAGS=-g -O3
LDFLAGS=-g -O3
LDLIBS=

all:${PROJECT}

bb: ${OBJS}
	cc ${LDFLAGS} -o $@ ${OBJS} ${LDLIBS}


clean:
	rm ${PROJECT} ${OBJS}


rsa.o: rsa.h
bb.o: rsa.h oracle.h bb.h
oracle.o: oracle.h rsa.h
main.o: rsa.h bb.h oracle.h
