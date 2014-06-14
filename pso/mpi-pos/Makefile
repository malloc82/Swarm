
SHELL   := /bin/bash
CURDIR  := $(shell pwd)
MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)

SRCDIR  := $(CURDIR)/src
TESTDIR := $(CURDIR)/test
INCLUDE := -I $(CURDIR)/include

# variables for compiling sequential code
SEQ_SRC := $(SRCDIR)/pso_seq_main.c \
		   $(SRCDIR)/functions.c \
		   $(SRCDIR)/utils.c

SEQ_OBJDIR := $(CURDIR)/obj_seq
SEQ_OBJ    := $(patsubst %.c,$(SEQ_OBJDIR)/%.c.o,$(notdir $(SEQ_SRC)))
SEQ_LIB    := 
CFLAGS     := 
LDFLAGS    := -lm

SEQ_EXEC := $(CURDIR)/pso_seq

# variables for compiling mpi code
MPI_SRC := $(SRCDIR)/pso_mpi_main.c \
		   $(SRCDIR)/functions.c \
		   $(SRCDIR)/utils.c

MPI_OBJDIR  := $(CURDIR)/obj_seq
MPI_OBJ     := $(patsubst %.c,$(MPI_OBJDIR)/%.c.o,$(notdir $(MPI_SRC)))
MPI_LIB     := 
MPI_CFLAGS  := $(shell $(MPICC) --showme:compile)
MPI_LDFLAGS := $(shell $(MPICC) --showme:link)

MPI_EXEC    := $(CURDIR)/pso_mpi

# Debugging flag

DEBUG := 

compile_seq: makedirectories $(SEQ_EXEC)

compile_mpi: makedirectories $(MPI_EXEC)

run:
	$(MPIRUN) -np 2 $(EXEC) 

# Rules for compiling sequential code

$(SEQ_EXEC): $(SEQ_SRC) $(SEQ_OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(SEQ_OBJ) -o $@

$(SEQ_OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(SEQ_OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@


# Rules for compiling mpi code

$(MPI_EXEC): $(MPI_SRC) $(MPI_OBJ)
	$(VERBOSE) $(CC) $(LIB) $(MPI_LDFLAGS) $(OBJ) -o $@

$(MPI_OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(MPI_CFLAGS) $(INCLUDE) -c $< -o $@

$(MPI_OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(MPI_CFLAGS) $(INCLUDE) -c $< -o $@


makedirectories:
	$(VERBOSE) mkdir -p $(SEQ_OBJDIR)
	$(VERBOSE) mkdir -p $(MPI_OBJDIR)

clean:
	$(VERBOSE) rm -rf $(SEQ_OBJDIR) $(MPI_OBJDIR) $(EXEC)
