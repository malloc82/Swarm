
CURDIR  := $(shell pwd)

SRCDIR  := $(CURDIR)/src
INCLUDE := -I $(CURDIR)/include
OBJDIR  := $(CURDIR)/obj

SRC     := $(SRCDIR)/floyd.c $(SRCDIR)/MyMPI.c
OBJ     := $(patsubst %.c,$(OBJDIR)/%.c.o,$(notdir $(SRC)))
LIB     := 
CFLAGS  := 
DEBUG   := 

EXEC    := $(CURDIR)/floyd

MPICC   := /opt/local/bin/mpicc-openmpi-mp
CC      := $(MPICC)
LINKER  := /usr/bin/clang 
# ARCH    := -arch x86_64
LDFLAGS := $(shell $(MPICC) --showme:link)

make_exec: makedirectories $(EXEC)

$(EXEC): $(SRC) $(OBJ)
	$(VERBOSE) $(LINKER) -v $(ARCH) $(LIB) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.c.o: $(SRC)
	$(VERBOSE) $(CC) $(DEBUG) $(INCLUDE) -c $< -o $@

makedirectories:
	$(VERBOSE) mkdir -p $(OBJDIR)

clean:
	$(VERBOSE) rm -rf $(OBJDIR) $(EXEC)
# floyd: floyd.o MyMPI.o
#	mpicc -o floyd floyd.o MyMPI.o
# floyd.o:
# 	mpicc -c floyd.c
# MyMPI.o:
# 	mpicc -c MyMPI.c
# clean:
# 	rm floyd floyd.o MyMPI.o 
