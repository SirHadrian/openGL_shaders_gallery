TARGET=window.out
SRCDIRS=.
INCDIRS=.

CC=gcc
LD=gcc

DEPFLAGS=-MP -MD
OPT=-O0

CFLAGS=$(DEPFLAGS) $(OPT) $(foreach D, $(INCDIRS), -I$(D)) -Wall -Wextra -Wconversion -Wuninitialized
LDFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lm -ldl

CFILES=$(foreach D, $(SRCDIRS), $(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.d window.out

-include $(DEPFILES)
