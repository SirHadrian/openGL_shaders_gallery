CC=gcc
LD=gcc
CFLAGS=-Wall -Wextra -Wconversion -Wuninitialized
LDFLAGS=-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl
OBJS=main.o glad.o stb_image.o
TARGET=window.out

all: ${TARGET}
	./${TARGET}

${TARGET}: ${OBJS}
	${LD} ${OBJS} ${LDFLAGS} -o ${TARGET}

%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	rm *.o window.out
