CC=gcc
SRC=main.c
DST=main

OBJS:=
OBJS += main.o
OBJS += item.o

%.o: %.c
	$(CC) -c -o $@ $<

build: $(OBJS)
	$(CC) -o $(DST) $^

run: build
	./$(DST)

clean:
	rm -rf $(OBJS) $(DST)