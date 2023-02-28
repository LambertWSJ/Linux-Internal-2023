CC=gcc
DST=main
CFLAGS += -Werror
OBJS:=
OBJS += main.o
OBJS += xor.o


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJS)
	$(CC) -o $(DST) $^ $(CFLAGS)

run: build
	./$(DST)

format:
	clang-format -i *.[ch]

clean:
	rm -rf $(OBJS) $(DST)