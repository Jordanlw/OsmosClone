#CC = $(NACL_SDK_ROOT)/toolchain/linux_x86_newlib/bin/i686-nacl-gcc
CC = colorgcc
CCARCH = -m64
CCFLAGS = -Wall -I $(NACL_SDK_ROOT)/toolchain/linux_x86_newlib/x86_64-nacl/usr/include \
-L $(NACL_SDK_ROOT)/toolchain/linux_x86_newlib/x86_64-nacl \
-lm -lppapi

SOURCES = $(wildcard *.c)
OBJSDIR = objs
OBJECTS = $(addprefix $(OBJSDIR)/, $(SOURCES:.c=.o))
OUTEXE = xOsmosClone.nexe
DEPSDIR = deps
DEPS = $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))

$(OUTEXE) : $(OBJECTS)
	$(CC) $(CCARCH) $(OBJECTS) $(CCFLAGS) -o $(OUTEXE)

-include $(DEPS)

$(OBJSDIR)/%.o : %.c
	$(CC) -MM $< > $(DEPSDIR)/$(<:.c=.d.tmp)
	@sed -e 's&^$(notdir $@)&$@&' < $(DEPSDIR)/$(<:.c=.d.tmp) > $(DEPSDIR)/$(<:.c=.d)
	$(CC) $(CCARCH) -c -o $@ $<

.PHONY : clean

clean :
	-rm $(OUTEXE) $(OBJECTS) $(addprefix $(DEPSDIR)/, $(SOURCES:.c=.d))
