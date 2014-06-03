
SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/src
INCLUDE := -I $(CURDIR)/include
OBJDIR  := $(CURDIR)/obj

SRC     := $(SRCDIR)/circuit.c $(SRCDIR)/MyMPI.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))
LIB     := 
CFLAGS  := 
DEBUG   := 

EXEC    := $(CURDIR)/circuit

MPICC   := $(shell which mpicc) # /opt/local/bin/mpicc-openmpi-mp
MPIRUN  := $(shell which mpirun)
CC      := $(shell $(MPICC) --showme:command)
# ARCH    := -arch x86_64
CFLAGS  := $(shell $(MPICC) --showme:compile)
LDFLAGS := $(shell $(MPICC) --showme:link)

make_exec: makedirectories $(EXEC)

run:
	$(MPIRUN) -np 2 $(EXEC) 

$(EXEC): $(SRC) $(OBJ)
	$(VERBOSE) $(CC) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(VERBOSE) $(CC) $(DEBUG) $(CFLAGS) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR) $(EXEC)
