CC=gcc
DST=main
CFLAGS += -W -Wall -Werror -g
OBJS:=
OBJS += main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJS)
	$(CC) -o $(DST) $^ $(CFLAGS)

run: build
	./$(DST)

clean:
	rm -rf $(OBJS) $(DST)