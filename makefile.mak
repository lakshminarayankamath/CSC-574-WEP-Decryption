CC=gcc
CFLAGS=-c -Wall -g 
LDFLAGS=
SOURCES=crack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=crack

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)
