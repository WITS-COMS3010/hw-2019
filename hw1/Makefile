#################
#   variables   #
#################

# files
EXECUTABLE  = shell
SOURCES  = main.c shell.c process.c io.c parse.c 
OBJECTS  = $(SOURCES:.c=.o)

# compilation and linking
CC      = gcc
CFLAGS  = -std=c99 -ggdb3 -c
LDFLAGS = 
WARN    = -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(WARN)
LINK.c    = $(CC)

#################
#     targets   #
#################

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.c) $^ $(LDFLAGS) -o $@

$(OBJECTS): %.o: %.c
	$(COMPILE.c) $< -o $@

# phony targets
.PHONY: clean

# remove object files, emacs temporaries
clean:
	rm -f *.o *~
