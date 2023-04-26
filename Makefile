# Compilation Flags
CC		= gcc
CFLAGS	= -Wall -O1 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

# Compilation Folders:
BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/
HDRDIR 	= headers/

# Add Objects here :
OBJECTS = \
	main.o \
	controller.o \
	game.o \
	render.o \
	scenery.o \
	utils.o \
	test.o \
	structs/colors.o \
	structs/vectors.o \
	structs/figures.o \
	structs/graphicObjects.o
# ---

_OBJECTS = $(addprefix $(OBJDIR), $(join $(OBJECTS), $(A)))
_OBJECTS_SIZE = $(words $(_OBJECTS))
_COUNTER = 0

# Exec Output Name
EXEC= TLC.out
# Exec Logging Output Name
EXECNAME = "The Light Corridor"


# Regles compilation TD 04

all : #main
	@echo "$(EXECNAME)| Compilation starting..."
	@echo "$(EXECNAME)| Compilator: $(CC),	Flags: $(CFLAGS)"
	@echo "$(EXECNAME)| Library: $(LDFLAGS)"
	@echo "$(EXECNAME)| -----"
	@echo "$(EXECNAME)| "
	@echo "$(EXECNAME)| Objects generation: <$(_OBJECTS_SIZE)>"
	@make -s start

start: main
	@echo "$(EXECNAME)| -----"
	@echo "$(EXECNAME)| "
	@echo "$(EXECNAME)| Compilation complete!"
	@echo "$(EXECNAME)| > Output : ./$(BINDIR)$(EXEC)"

main : $(_OBJECTS)
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	echo "$(EXECNAME)| [$(_COUNTER)/$(_OBJECTS_SIZE)] + $@ : $^"
	$(CC) $(CFLAGS) $^ -o $(BINDIR)$(EXEC) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c $(HDRDIR)%.h
	echo "$(EXECNAME)| [$(_COUNTER)/$(_OBJECTS_SIZE)] + $@ : $^"
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)
	$(eval _COUNTER=$(shell echo $$(($(_COUNTER) + 1))))
	

$(OBJDIR)%.o: $(SRCDIR)%.c
	echo "$(EXECNAME)| [$(_COUNTER)/$(_OBJECTS_SIZE)] + $@ : $^"
	mkdir -p `dirname $@`
	$(CC) -o $@ -I $(HDRDIR) -c $< $(CFLAGS)
	$(eval _COUNTER=$(shell echo $$(($(_COUNTER) + 1))))
