SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/../../c_mpi
TESTDIR := $(CURDIR)
INCLUDE := -I $(CURDIR)/../../../include
OBJDIR  := $(CURDIR)/obj
BINDIR  := $(TESTDIR)/bin

SRC     := $(SRCDIR)/pso_mpi_comm.c $(SRCDIR)/utils.c $(TESTDIR)/comm_test.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))

EXEC    := $(BINDIR)/comm_test

# Tools
MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
CFLAGS  := $(shell $(MPICC) --showme:compile) -Wall
LDFLAGS := $(shell $(MPICC) --showme:link)

compile: makedirectories $(EXEC)

$(EXEC): $(SRC) $(OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

test: $(EXEC)
	mpirun -np 5 $(EXEC)

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR) 
	$(VERBOSE) mkdir -p $(BINDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR)
	$(VERBOSE) rm -rf $(BINDIR)
