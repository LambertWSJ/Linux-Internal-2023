CC = gcc
EXE = mpmc
CFLAGS := 
LDLAGS := 
OBJS := 
SANITIZE := 0

CFLAGS += -Wall
CFLAGS += -std=c11
LDLAGS += -lpthread

OBJS += main.o


ifeq ($(SANITIZE), 1)
CFLAGS += -fsanitize=thread
endif


%.o:%.c
	$(CC) -c $@ $< $(CFLAGS) $(LDLAGS)

build: $(OBJS)
	$(CC) -o $(EXE) $^

run: build
	./$(EXE)

clean:
	rm -rf $(EXE) *.o