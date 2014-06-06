
SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/src
TESTDIR := $(CURDIR)/test
INCLUDE := -I $(CURDIR)/include
OBJDIR  := $(CURDIR)/obj

SRC     := $(SRCDIR)/functions.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))
LIB     := 
CFLAGS  := 
DEBUG   := 

EXEC    := $(CURDIR)/comm_test

MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
CFLAGS  := $(shell $(MPICC) --showme:compile)
LDFLAGS := $(shell $(MPICC) --showme:link)

compile: makedirectories $(EXEC)

run:
	$(MPIRUN) -np 2 $(EXEC) 

ackley_test:


$(EXEC): $(SRC) $(OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR) $(EXEC)
