CC = gcc
EXE = work-steal
CFLAGS := 
LDLAGS := 
OBJS := 

CFLAGS += -O2
CFLAGS += -Wall
CFLAGS += -std=c11
LDLAGS += -lpthread

OBJS += main.o

%.o:%.c
	$(CC) -c $@ $< $(CFLAGS) $(LDLAGS)

build: $(OBJS)
	$(CC) -o $(EXE) $^

run: build
	./$(EXE)

clean:
	rm -rf $(EXE) *.o