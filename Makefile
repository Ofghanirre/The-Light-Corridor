CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/
HDRDIR 	= headers/


EXEC= TLC.out

# Regles compilation TD 04

all : main #main

main : $(OBJDIR)main.o $(OBJDIR)controller.o $(OBJDIR)game.o $(OBJDIR)render.o
	$(CC) $(CFLAGS) $(OBJDIR)main.o -o $(BINDIR)$(EXEC) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c $(HDRDIR)%.h
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)
