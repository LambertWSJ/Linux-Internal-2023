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
	
format:
	clang-format -i *.[ch]
clean:
	rm -rf $(OBJS) $(DST)