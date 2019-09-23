SRC=allocator.c main.c
EXEC=main

CC=gcc
WARN=-Wall -Wextra -Wno-unused-parameter
CFLAGS=-std=c99 -ggdb3 $(WARN)
LDFLAGS=

OBJS=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@  

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXEC) $(OBJS)
