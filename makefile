CC = gcc
CCFLAGS = -Wall -g -lSDL
SOURCES = $(wildcard *.c)
SOURCES := $(filter-out varArray.c undoOverlap.c, $(SOURCES))
OBJECTS = $(SOURCES:.c=.o)
OUTEXE = xOsmosClone
DEPSDIR = deps

$(OUTEXE) : $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(OUTEXE)

-include $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))

%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@
	$(CC) -MM $< > $(addprefix $(DEPSDIR)/, $(@:.o=.d))

.PHONY : clean

clean :
	-rm $(OUTEXE) $(OBJECTS) $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))
