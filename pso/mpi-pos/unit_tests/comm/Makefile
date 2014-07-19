SHELL   := /bin/bash
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/../../src
TESTDIR := $(CURDIR)
INCLUDE := -I $(CURDIR)/../../include
OBJDIR  := $(CURDIR)/obj
BINDIR  := $(TESTDIR)/bin

SRC     := $(SRCDIR)/pso_mpi_comm.c $(TESTDIR)/neighbors_test.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))
