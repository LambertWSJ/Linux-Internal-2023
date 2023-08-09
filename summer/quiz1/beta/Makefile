CC = gcc
EXE=main
ALIGN_SZ = -1
CFLAGS :=
OBJS :=

CFLAGS+= -O2
OBJS += main.o

ifeq ($(ALIGN_SZ), -1)
CFLAGS += -DALIGN_SZ=4
else
CFLAGS += -DALIGN_SZ=$(ALIGN_SZ)
endif

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

build: $(OBJS)
	$(CC) -o $(EXE) $^

run: build
	./$(EXE)

clean:
	rm -rf *.o $(EXE)