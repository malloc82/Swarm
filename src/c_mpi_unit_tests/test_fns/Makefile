
SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/../../c_mpi
TESTDIR := $(CURDIR)
INCLUDE := -I $(CURDIR)/../../../include
OBJDIR  := $(CURDIR)/obj
BINDIR  := $(CURDIR)/bin

COMMON_SRC := $(SRCDIR)/functions.c $(SRCDIR)/utils.c $(SRCDIR)/io.c
COMMON_OBJ := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(COMMON_SRC)))
DEBUG      := -g

MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
CFLAGS  := -Wall # $(shell $(MPICC) --showme:compile)
LDFLAGS := -lm # $(shell $(MPICC) --showme:link)

ACKLEY_SRC    := $(TESTDIR)/ackley.c
ACKLEY_OBJ    := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(ACKLEY_SRC)))
ACKLEY_EXEC   := $(BINDIR)/ackley

MICHAL_SRC    := $(TESTDIR)/michalewicz.c
MICHAL_OBJ    := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(MICHAL_SRC)))
MICHAL_EXEC   := $(BINDIR)/michalewicz

RASTRIGIN_SRC  := $(TESTDIR)/rastrigin.c
RASTRIGIN_OBJ  := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(RASTRIGIN_SRC)))
RASTRIGIN_EXEC := $(BINDIR)/rastrigin

compile: makedirectories ackley_bin michal_bin rastrigin_bin

ackley_bin:    $(ACKLEY_EXEC)

michal_bin:    $(MICHAL_EXEC)

rastrigin_bin: $(RASTRIGIN_EXEC)

$(ACKLEY_EXEC): $(COMMON_SRC) $(ACKLEY_SRC) $(COMMON_OBJ) $(ACKLEY_OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(COMMON_OBJ) $(ACKLEY_OBJ) -o $@

$(MICHAL_EXEC): $(COMMON_SRC) $(MICHAL_SRC) $(COMMON_OBJ) $(MICHAL_OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(COMMON_OBJ) $(MICHAL_OBJ) -o $@

$(RASTRIGIN_EXEC): $(COMMON_SRC) $(RASTRIGIN_SRC) $(COMMON_OBJ) $(RASTRIGIN_OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(COMMON_OBJ) $(RASTRIGIN_OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.c.o: $(TESTDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR)
	$(VERBOSE) mkdir -p $(BINDIR)

clean:
	$(VERBOSE) rm -f $(COMMON_OBJ) $(ACKLEY_OBJ) $(MICHAL_OBJ) $(RASTRIGIN_OBJ) 
	$(VERBOSE) rm -f $(ACKLEY_EXEC) $(MICHAL_EXEC) $(RASTRIGIN_EXEC)
