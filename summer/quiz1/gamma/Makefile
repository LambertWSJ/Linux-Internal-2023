CC = gcc
EXE=qsort
CFLAGS :=
OBJS :=

CFLAGS+= -Wall
CFLAGS+= -lpthread
CFLAGS+= -D__STDC_WANT_LIB_EXT2__=1
CFLAGS+= -D_GNU_SOURCE
OBJS += main.o

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

build: $(OBJS)
	$(CC) -o $(EXE) $^

run: build
	./$(EXE)

clean:
	rm -rf *.o $(EXE)