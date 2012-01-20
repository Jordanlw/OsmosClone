CC = gcc
CCFLAGS = -Wall -g -lSDL -lm
SOURCES = $(wildcard *.c)
SOURCES := $(filter-out varArray.c undoOverlap.c, $(SOURCES))
OBJSDIR = objs
OBJECTS = $(addprefix $(OBJSDIR)/, $(SOURCES:.c=.o))
OUTEXE = xOsmosClone
DEPSDIR = deps
DEPS = $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))
DEPSCUR = $(DEPSDIR)/$(<:.c=.d)

$(OUTEXE) : $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $(OUTEXE)

-include $(DEPS)

$(OBJSDIR)/%.o : %.c
	$(CC) $(CCFLAGS) -MM $< > $(DEPSDIR)/$(<:.c=.d.tmp)
	sed -e 's&^$(notdir $@)&$@&' < $(DEPSDIR)/$(<:.c=.d.tmp) > $(DEPSDIR)/$(<:.c=.d)
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY : clean

clean :
	-rm $(OUTEXE) $(OBJECTS) $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))
