CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/
HDRDIR 	= headers/


EXEC= TLC.out

EXECNAME = "The Light Corridor"
# Regles compilation TD 04

all : #main
	@echo "$(EXECNAME)| Compilation starting..."
	@echo "$(EXECNAME)| Compilator: $(CC),	Flags: $(CFLAGS)"
	@echo "$(EXECNAME)| Library: $(LDFLAGS)"
	@echo "$(EXECNAME)| -----"
	@echo "$(EXECNAME)| "
	@echo "$(EXECNAME)| Objects generation:"
	@make -s start

start: main
	@echo "$(EXECNAME)| -----"
	@echo "$(EXECNAME)| "
	@echo "$(EXECNAME)| Compilation complete!"

main : $(OBJDIR)main.o $(OBJDIR)controller.o $(OBJDIR)game.o $(OBJDIR)render.o
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	echo "$(EXECNAME)| + $@ : $^"
	$(CC) $(CFLAGS) $^ -o $(BINDIR)$(EXEC) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c $(HDRDIR)%.h
	echo "$(EXECNAME)| + $@ : $^"
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)
	

$(OBJDIR)%.o: $(SRCDIR)%.c
	echo "$(EXECNAME)| + $@ : $^"
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)
