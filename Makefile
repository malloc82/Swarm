floyd: floyd.o MyMPI.o
g	mpicc -o floyd floyd.o MyMPI.o
floyd.o:
	mpicc -c floyd.c
MyMPI.o:
	mpicc -c MyMPI.c
clean:
	rm floyd floyd.o MyMPI.o 
