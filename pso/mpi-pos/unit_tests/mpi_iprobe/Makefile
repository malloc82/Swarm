SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/../../src
TESTDIR := $(CURDIR)
INCLUDE := -I $(CURDIR)/../../include
OBJDIR  := $(CURDIR)/obj
BINDIR  := $(TESTDIR)/bin

SRC     := $(TESTDIR)/test_main.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))

EXEC    := $(BINDIR)/mpi_iprobe_test

# Tools
MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
CFLAGS  := $(shell $(MPICC) --showme:compile)
LDFLAGS := $(shell $(MPICC) --showme:link)

compile: makedirectories $(EXEC)

$(EXEC): $(SRC) $(OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR) 
	$(VERBOSE) mkdir -p $(BINDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR)
	$(VERBOSE) rm -rf $(BINDIR)

mpi_run:
	$(MPIRUN) -n 2 $(EXEC)
