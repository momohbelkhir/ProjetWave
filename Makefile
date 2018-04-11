EXEC=App
SOURCES=menu.c wave.c args.c main.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-W -Wall
 
.PHONY: default clean
 
default: $(EXEC)
 
menu.o: menu.c menu.h
wave.o: wave.c wave.h 
args.o: args.c args.h
main.o: main.c menu.h wave.h args.h
 
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
 
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^
 
clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~
