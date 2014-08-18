SHELL   := /bin/bash
CURDIR  := $(shell pwd)

# MPIPATH := /usr/local/openmpi/1.6.5
MPIPATH := /usr/local/openmpi/1.8.1
MPICC   := $(MPIPATH)/bin/mpicc
MPIRUN  := $(MPIPATH)/bin/mpirun
CC      := $(shell $(MPICC) --showme:command)

SRCDIR  := $(CURDIR)/src
TESTDIR := $(CURDIR)/test
INCLUDE := -I $(CURDIR)/include
BINDIR  := $(CURDIR)/bin

# variables for compiling sequential code
SEQ_SRC := $(SRCDIR)/pso_seq_main.c \
		   $(SRCDIR)/search.c \
		   $(SRCDIR)/agents.c \
		   $(SRCDIR)/functions.c \
		   $(SRCDIR)/utils.c \
		   $(SRCDIR)/io.c \
		   $(SRCDIR)/profiler.c

SEQ_OBJDIR := $(CURDIR)/obj_seq
SEQ_OBJ    := $(patsubst %.c,$(SEQ_OBJDIR)/%.c.o,$(notdir $(SEQ_SRC)))
SEQ_LIB    := 
CFLAGS     := -Wall
LDFLAGS    := -lm

SEQ_EXEC := $(BINDIR)/pso_seq

# variables for compiling mpi code
MPI_SRC := $(SRCDIR)/pso_mpi_main.c \
		   $(SRCDIR)/search.c \
		   $(SRCDIR)/agents.c \
		   $(SRCDIR)/functions.c \
		   $(SRCDIR)/utils.c \
		   $(SRCDIR)/io.c \
		   $(SRCDIR)/profiler.c

MPI_OBJDIR  := $(CURDIR)/obj_mpi
MPI_OBJ     := $(patsubst %.c,$(MPI_OBJDIR)/%.c.o,$(notdir $(MPI_SRC)))
MPI_LIB     := 
MPI_CFLAGS  := $(shell $(MPICC) --showme:compile) -Wall
MPI_LDFLAGS := $(shell $(MPICC) --showme:link)

MPI_EXEC    := $(BINDIR)/pso_mpi

# Debugging flag

DEBUG := -g

compile_seq: makedirectories $(SEQ_EXEC)

compile_mpi: makedirectories $(MPI_EXEC)

mpi_run:
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
	$(VERBOSE) $(CC) $(LIB) $(MPI_LDFLAGS) $(MPI_OBJ) -o $@

$(MPI_OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(MPI_CFLAGS) $(INCLUDE) -c $< -o $@

$(MPI_OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(MPI_CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(BINDIR)
	$(VERBOSE) mkdir -p $(SEQ_OBJDIR)
	$(VERBOSE) mkdir -p $(MPI_OBJDIR)

clean:
	$(VERBOSE) rm -rf $(SEQ_OBJDIR) $(MPI_OBJDIR) $(SEQ_EXEC) $(MPI_EXEC)
mpi_clean: 
	$(VERBOSE) rm -rf $(MPI_OBJDIR) $(MPI_EXEC)
seq_clean:
	$(VERBOSE) rm -rf $(SEQ_OBJDIR)  $(SEQ_EXEC)
seq_run:	
	$(SEQ_EXEC) --ranges="-5,5;-5,5" \
				--agents_count=100 \
				--precision=0.001 \
				--max_runs=100 \
				--fn=rastrigin \
				-w 1 -a 1 -b 2 \
				--expected=0.0 \
				--test_runs=20 \
				--verbose
