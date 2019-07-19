SRCDIR	= ../../src
EXTDIR	= ext
HDRDIR  = hdr
OBJDIR	= obj
BINDIR	= ./
DEPDIR	= dep
DATDIR	= data

CC	= gcc
TARGET	= chat
CFLAGS	= -std=c99 -Ofast -msse2 -march=native -Wall -Wextra -Wpedantic -I$(HDRDIR)
LFLAGS	=

SOURCES	:= $(wildcard $(SRCDIR)/*.c)
BINARIES:= $(wildcard $(BINDIR)/*.c)
EXTERNS	:= $(wildcard $(EXTDIR)/*.c)
HEADERS := $(wildcard $(HDRDIR)/*.h)
OBJECTS	:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXAMPLES:= $(BINARIES:$(BINDIR)/%.c=$(OBJDIR)/%.o)
EXT_OBJ	:= $(EXTERNS:$(EXTDIR)/%.c=$(OBJDIR)/%.o)
DEPS	:= $(OBJECTS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

REMOVE	:= rm -rf

# Linking
$(TARGET): $(OBJECTS) $(EXT_OBJ) $(CMN_OBJ) $(EXAMPLES)
		$(CC) $(LFLAGS) -o $@ $(OBJECTS) $(EXT_OBJ) $(CMN_OBJ) $(EXAMPLES)
		@echo "Linking complete"

-include $(DEPS)

# Compilation
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
		mkdir -p $(OBJDIR)
		mkdir -p $(DEPDIR)
		$(CC) -c $(CFLAGS) $< -o $@
		$(CC) -I$(HDRDIR) -MM -MT '$(OBJDIR)/$*.o' $(SRCDIR)/$*.c > $(DEPDIR)/$*.d
		@echo "Compiled $<"

$(EXAMPLES): $(OBJDIR)/%.o : $(BINDIR)/%.c
		mkdir -p $(OBJDIR)
		mkdir -p $(DEPDIR)
		$(CC) -c $(CFLAGS) $< -o $@
		$(CC) -I$(HDRDIR) -MM -MT '$(OBJDIR)/$*.o' $(BINDIR)/$*.c > $(DEPDIR)/$*.d
		@echo "Compiled $<"

$(EXT_OBJ): $(OBJDIR)/%.o : $(EXTDIR)/%.c
		mkdir -p $(OBJDIR)
		mkdir -p $(DEPDIR)
		$(CC) -c $(CFLAGS) $< -o $@
		$(CC) -I$(HDRDIR) -MM -MT '$(OBJDIR)/$*.o' $(EXTDIR)/$*.c > $(DEPDIR)/$*.d
		@echo "Compiled $<"

.PHONY: clean
clean:
#$(REMOVE) $(OBJECTS) $(OBJDIR) $(BINDIR) $(DEPDIR)
		$(REMOVE) $(OBJECTS) $(OBJDIR) $(DEPDIR) $(TARGET)
		@echo "Deleted $<"

.PHONY: all
all: $(BINDIR)/$(TARGET)
