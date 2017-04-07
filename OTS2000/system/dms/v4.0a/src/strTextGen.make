## -*- Makefile -*-
##
## User: ems
## Time: 2006-6-29 11:26:24
## Makefile created by Sun Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
include ../../../global.make

CFLAGS = $(BASICOPTS) -c

# Define the target directories.
TARGETDIR=.
TARGET=strTextGen.$(SUFFIX)

all: $(TARGETDIR)/$(TARGET)

OBJS =  \
	$(TARGETDIR)/strTextGen.o

USERLIBS = ../lib/dblib.lib ../../../dps/v4.0a/lib/ipclib.lib $(SYSLIBS) 
DEPLIBS = 
LDLIBS = $(USERLIBS)


# Link or archive
$(TARGETDIR)/$(TARGET): $(TARGETDIR) $(OBJS) $(DEPLIBS)
	$(LINK) -o $@ $(OBJS) $(LDLIBS)


# Compile source files into .o files
$(TARGETDIR)/strTextGen.o: $(TARGETDIR) strTextGen.c
	$(COMPILE) $(CFLAGS) $(CPPFLAGS) -o $@ strTextGen.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR)/$(TARGET) \
		$(OBJS)
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state
