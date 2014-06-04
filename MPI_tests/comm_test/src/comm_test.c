#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void schedule(const int id, const int p) 
{
    switch(id) {
        case 0:  
            /* monitor(id, p);  */
            receiver_test(id, p);
            break;
        case 1:
            sender_test(id, p);
            break;
        default: 
            worker(id); 
            break;
    }
    return;
}

int monitor(const int id, const int p) 
{
    int i;
    int data;
    MPI_Status status;
    printf("----------> This is root node, id = %d\n", id);
    for (i = 1; i < p; i++) {
        if (i == 5) {
            puts("\nzzzzzzzzzzzzz delaying node 0 ... \n");
            sleep(5);
            puts("\nooooooooooooo node 0 woke up\n");
        }
        
        /* MPI_Recv(&data, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status); */
        /* printf("\n >>>>>>>>>> root node: data recieved from node %d, data = %d\n\n", i, data); */
    }
    return id;
}

int worker(const int id)
{
    int data = id;
    /* printf("= = = = = =>This is child node, id = %d\n", id); */
    MPI_Send(&data, 1, MPI_INT, 0, id, MPI_COMM_WORLD);
    printf("\n<<<<<<<< node %d: data sent\n\n", id);
    return id;
}

int receiver_test(const int id, const int p)
{
    char data[50]; 
    MPI_Status status;
    puts("zzzzzzzzzz: reciever delay");
    sleep(5);
    puts("woooooooow: receiver wake up");

    MPI_Recv(&data, 50, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
    printf("Receiver: data(2) = %s\n", data);

    MPI_Recv(&data, 50, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
    printf("Receiver: data(1) = %s\n", data);

    MPI_Recv(&data, 50, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
    printf("Receiver: data(0) = %s\n", data);
    
    return 0;
}

int sender_test(const int id, const int p) 
{
    const char * msg1 = " message 1";
    const char * msg2 = " message 2    ";
    const char * msg3 = "   third message ";

    MPI_Send((void *)msg1, strlen(msg1) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    MPI_Send((void *)msg2, strlen(msg2) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    MPI_Send((void *)msg3, strlen(msg3) + 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    
    puts("# # # # #   sender done.");

    return 0;
}

int main(int argc, char *argv[])
{
    int id = -1; /* uninitialized */
    int p  = -1; /* uninitialized */
    printf("begin: id = %d, p = %d\n", id, p);
    clock_t start = clock(), diff;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    diff = clock() - start;
    double msc = diff * 1000/CLOCKS_PER_SEC;
    if (id == 0) {
        printf(" ******* Initialization too %f ms *******\n", diff);
    }
    
    printf("after init: id = %d, p %d \n", id, p);
    
    schedule(id, p);
    
    printf("done: id = %d\n", id);
    MPI_Finalize();
    return 0;
}
