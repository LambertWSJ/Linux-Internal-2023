CC = gcc
EXE=main
CFLAGS :=
OBJS :=

CFLAGS+= -O2
CFLAGS+= -lpthread
OBJS += main.o

ENABLE_GDB = 0

ifeq ($(ENABLE_GDB), 1)
CFLAGS += -g
endif

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

build: $(OBJS)
	$(CC) -o $(EXE) $^

run: build
	./$(EXE)

clean:
	rm -rf *.o $(EXE)