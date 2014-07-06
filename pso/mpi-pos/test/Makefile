
SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/../src
TESTDIR := $(CURDIR)
INCLUDE := -I $(CURDIR)/../include
OBJDIR  := $(CURDIR)/obj

SRC     := $(SRCDIR)/functions.c $(SRCDIR)/utils.c
TESTSRC := $(TESTDIR)/fn_tests.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))
OBJ     += $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(TESTSRC)))
LIB     := -lm
DEBUG   := 

EXEC    := $(CURDIR)/fn_tests

MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
CFLAGS  := # $(shell $(MPICC) --showme:compile)
LDFLAGS := # $(shell $(MPICC) --showme:link)

compile: makedirectories $(EXEC)

# run:
# 	$(MPIRUN) -np 2 $(EXEC) 

$(EXEC): $(SRC) $(TESTSRC) $(OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR) $(EXEC)
