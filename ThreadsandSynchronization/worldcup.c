#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
/*the above are the libraries needed for accessing function for semaphores, threads, and etc.*/

static sem_t connected_lock;
static sem_t operators;
static int NUM_OPERATORS = 3;
static int NUM_LINES = 5;
static int connected = 0; // Callers that are connected
void* phonecall(void* vargp);

static int next_id = 0; // global variable that will be used for the creation of a unique id for each thread    

/* declaration of helper functions*/
void clean(); // helper function that destroys the semaphores
void* wait_func(void* vargp); // function for the thread that is used as a timer in which the main thread uses pthread_join on this thread

// void* increment(void* vargp);


int main(int argc, char *argv[]) {
    pthread_t* tids[100]; // declaration of the array of thread ids that represents each phone call
    pthread_t timer; // thread used as a timer to simulate the actual press conference
    int seconds = atoi(argv[1]); // the total seconds of the conference
    int ret_value; // return value for the wait_func
    int thread_val; // this variable will be used for error handling on the pthread functions

    // this if statement is checking if the command line argument given is valid
    if (seconds <= 0) {
        printf("Invalid argument for the total seconds of the conference (argument has to be a number greater than zero)!\n");
        exit(0);
    }

    sem_init(&connected_lock, 0, 1); // initialization of the binary semaphore connected_lock
    sem_init(&operators, 0, NUM_OPERATORS); // initialization of the counting semaphore operators
    
    // loop for the creation of the phonecall threads
    for (int i = 0; i < 100; i++) {
        thread_val = pthread_create(&tids[i], NULL, phonecall, (void *) (i));

        // error handling
        if (thread_val != 0) {
            printf("Error creating thread: %d\n", thread_val);
            exit(0);
        }
    }
    // creation of the thread that is used to simulate the actual press conference in which the total seconds of conference is passed as an argument
    thread_val = pthread_create(&timer, NULL, wait_func, (void*) seconds);

    // error handling
    if (thread_val != 0) {
        printf("Error creating thread: %d\n", thread_val);
        exit(0);
    }

    // joining the main thread and wait_func thread
    thread_val = pthread_join(timer, (void**)(&ret_value));
    
    // error handling
    if (thread_val != 0) {
        printf("Error joining thread: %d\n", thread_val);
        exit(0);
    }

    // destroying the seamphore before exiting
    clean();
    exit(0);
}


/*Definition of functions declared above the main*/
void* phonecall(void* vargp) {  
    int id = next_id; // caller's id as a function local variable
    next_id++; // incrementing the global variable next_id for the assignment to the id variable inside the thread function

    // Printing that an attempt to connect has been made.
    printf("Thread %d is attempting to connect to the conference center ...\n", id);

    // checking if the line is busy, in which case there is a wait for one second
    sem_wait(&connected_lock);
    while (connected >= NUM_LINES) {
        sem_post(&connected_lock);
        sleep(1);
        sem_wait(&connected_lock);
    }
    connected++;
    sem_post(&connected_lock);
    
    // if the line is not connected then connected is updated
    printf("Thread %d connects to an available line, call ringing ...\n", id);
    
    // waiting for an operator to be available
    sem_wait(&operators);
    // printing the message that the question is being taken by an operator
    printf("Thread %d is speaking to an operator.\n", id);
    // simulation of a question proposal by sleeping for one second
    sleep(1);
    // printing a message that the question proposal is complete
    printf("Thread %d has proposed a question for the USA soccer team! The operator has left ...\n", id);
    sem_post(&operators);

    // updating connected as the thread is done doing a phone call
    sem_wait(&connected_lock);
    connected--;
    sem_wait(&connected_lock);
    // printing a message that the call is over
    printf("Thread %d has hung up!\n", id);

    // use of pthread_detach to mark the thread as detached
    pthread_detach(pthread_self());
    return NULL; // return of NULL as this thread function isn't supposed to return any specific type of value that might be used in other parts of the program
}

void clean(){
    sem_destroy(&connected_lock);
    sem_destroy(&operators);
}

void* wait_func(void* vargp) {
    int seconds = (int)vargp;
    sleep(seconds);
    return 0;  // return of an arbitrary value like 0 that's only used for pthread_join.
}