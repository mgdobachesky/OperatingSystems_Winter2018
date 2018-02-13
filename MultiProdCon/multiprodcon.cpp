/**
 * Simple program demonstrating shared memory in POSIX systems.
 * Producer - Consumer Battle
*/
//*************************************************************
//*************************************************************
// Declarations
//*************************************************************
#include <signal.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
//#include <sys/stat.h>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

// Number of widget slots
#define BUFFER_SIZE 200
#define MAX_THREADS 5
#define RANDOM_MOD 5


/*
 \033[22;30m - black
 \033[22;31m - red
 \033[22;32m - green
 \033[22;33m - brown
 \033[22;34m - blue
 \033[22;35m - magenta
 \033[22;36m - cyan
 \033[22;37m - gray
 \033[01;30m - dark gray
 \033[01;31m - light red
 \033[01;32m - light green
 \033[01;33m - yellow
 \033[01;34m - light blue
 \033[01;35m - light magenta
 \033[01;36m - light cyan
 \033[01;37m - white

 */
#define VT_RESET  "\033[0m"

#define VT_BLACK  "\033[1;30m"
#define VT_RED    "\033[7;31m"
#define VT_GREEN  "\033[0;1;32m"
#define VT_BROWN  "\033[1;33m"
#define VT_BLUE   "\033[0;1;34m"
#define VT_MAGENTA  "\033[1;35m"
#define VT_CYAN   "\033[1;36m"

// Seconds to run factory simulation
#define SIM_LENGTH 30

void* producer(void* args);
void* consumer(void* args);
void makeWidget(int tid);
void eatWidget(int tid);
void  printMenu();

/* Structure to hold shared data */
typedef struct {
    int next_in;
    int next_out;
    int widget_count;
    int buffer[BUFFER_SIZE];
} widget_factory_t;

/* a pointer to the shared memory segment */
widget_factory_t* shared_factory;

//**********************
// Semaphore Sweetness
pthread_mutex_t count_lock;
sem_t empty_slots;
sem_t full_slots;

//*************************************************************
//*************************************************************
// main function
//*************************************************************
//*************************************************************
int main()
{

    //*************************************************************
    // Initializations
    //*************************************************************
    pthread_mutex_init(&count_lock, NULL);
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    // These arrays hold the system tids of the threads
    pthread_t producer_tid[MAX_THREADS];
    pthread_t consumer_tid[MAX_THREADS];

    // These are the local tids for output
    int tids[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++)
        tids[i]= i + 1;

    // For check return codes from functions
    int returnCode = 0;

    // Allocate memory for the Widget Factory
    shared_factory = new widget_factory_t;

    // Assume we need more tests
    bool moreTests = true;

    // Assume an invalid input choice
    int userChoice = -1;

    // do simulations
    do {
        //*************************************************************
        // Initialize factory for this test run
        shared_factory->next_in = 0;
        shared_factory->next_out = 0;
        shared_factory->widget_count = 0;

        //*************************************************************
        // Get the test user wants to run
        printMenu();
        std::cin >> userChoice;

        switch(userChoice) {

            //*************************************************************
            // Case 1: Run as functions
            case 1: {
                int loopCount = 0;
                std::cout << "\nHow many producer/consumer loops should I do? ";
                std::cin >> loopCount;

                int functionID = -1;

                for(int i = 0; i<loopCount; i++) {
                    int numWidgetsToProduce = rand() % RANDOM_MOD;
                    for (int j = 0; j < numWidgetsToProduce; j++)
                        producer(&functionID);

                    int numWidgetsToConsume = rand() % RANDOM_MOD;
                    for (int j = 0; j < numWidgetsToConsume; j++)
                        consumer(&functionID);

                } // end Prod/Con Loop
                printf(VT_RESET);
                printf("Parent killed both children!\n");
            } // End Case 1
                break;

                //*************************************************************
                // Case 2: Spawn One Produce and Consumer Thread Each
            case 2: {

                // Launch threads
                pthread_create(&producer_tid[0], NULL, producer, &tids[0]);
                pthread_create(&consumer_tid[0], NULL, consumer, &tids[0]);

                printf("Parent sleeping for %d seconds to let simulation run \n", SIM_LENGTH);
                sleep(SIM_LENGTH);

                /* kill producer */
                returnCode = pthread_cancel(producer_tid[0]);
                /* kill consumer */
                returnCode = pthread_cancel(consumer_tid[0]);
                printf(VT_RESET);
                printf("Parent killed both children!\n");

            } // End Case 2
                break;

                //*************************************************************
                // Case 3: Multiple producer and consumer threads
            case 3: {

                for (int i = 0; i < MAX_THREADS; i++) {
                    pthread_create(&producer_tid[i], NULL, producer, &tids[i]);
                    pthread_create(&consumer_tid[i], NULL, consumer, &tids[i]);
                }

                /* parent to time simulation */
                printf("Parent sleeping for %d seconds to let simulation run \n", SIM_LENGTH);
                sleep(SIM_LENGTH);
                for (int i = 0; i < MAX_THREADS; i++) {
                    /* kill producers */
                    returnCode = pthread_cancel(producer_tid[i]);
                    /* kill consumers */
                    returnCode = pthread_cancel(consumer_tid[i]);
                }
                printf(VT_RESET);
                printf("Parent killed both children!\n");
            } // End case 3
                break;

                // Case 9:  // End testing
            case 9:
                moreTests = false;
                break;

                // Default case:  - Bad user input
            default:
                std::cout << "Please select a choice from the menu!\n";

        } // End test selection switch statement

    } while (moreTests); // end do-while

    // Reset terminal colors before exiting
    printf(VT_RESET);

    return 0;
}

//*************************************************************
//*************************************************************
// primary producer function
//*************************************************************
//*************************************************************
void* producer(void* arg)
{
    int* tid = (int *)arg;
    if (*tid < 0)
    {
        if (shared_factory->widget_count < BUFFER_SIZE)
            makeWidget(*tid);
    }
    else
    {
        while(1) //loop until death
        {
            //while (shared_factory->widget_count == BUFFER_SIZE) ;
            sem_wait(&empty_slots);
            int sleepSeconds = rand() % RANDOM_MOD;
            sleep(sleepSeconds);
            makeWidget(*tid);
            sem_post(&full_slots);
        }
    }
    //pthread_exit(0);
}

//*************************************************************
//*************************************************************
// producer helper to make widgets function
//*************************************************************
//*************************************************************
void makeWidget(int tid)
{
    pthread_mutex_lock(&count_lock);
    // set value of next in
    int temp = shared_factory->next_in;
    shared_factory->buffer[temp] = rand();
    // increment circular array and widget count
    shared_factory->next_in = (shared_factory->next_in + 1) % BUFFER_SIZE;
    shared_factory->widget_count = (shared_factory->widget_count + 1);
    pthread_mutex_unlock(&count_lock);

    if (shared_factory->widget_count > BUFFER_SIZE)
        printf(VT_RED);
    else {
        printf(VT_BROWN);
    }
    printf("Producer %d produced in slot %d! %d widgets now available!\n",
           tid, temp, shared_factory->widget_count);

}

//*************************************************************
//*************************************************************
// primary consumer function
//*************************************************************
//*************************************************************
void* consumer(void* arg) {
    int* tid = (int *)arg;
    if (*tid < 0)
    {
        if(shared_factory->widget_count > 0)
            eatWidget(*tid);
    }
    else
    {
        while(1) //loop until death
        {
            //while (shared_factory->widget_count == 0) ;
            sem_wait(&full_slots);
            int sleepSeconds = rand() % RANDOM_MOD;
            sleep(sleepSeconds);
            eatWidget(*tid);
            sem_post(&empty_slots);
        }
    }
    //pthread_exit(0);
}

//*************************************************************
//*************************************************************
// consumer helper to eat widgets function
//*************************************************************
//*************************************************************
void eatWidget(int tid)
{
    pthread_mutex_lock(&count_lock);
    // get the widget to each
    int temp = shared_factory->next_out;
    int eat_widget = shared_factory->buffer[temp];
    // decrement circular array and widget count
    shared_factory->next_out = (shared_factory->next_out + 1) % BUFFER_SIZE;
    shared_factory->widget_count = (shared_factory->widget_count - 1);
    pthread_mutex_unlock(&count_lock);

    if (shared_factory->widget_count < 0)
        printf(VT_RED);
    else
    {
        printf(VT_CYAN);
    }
    printf("* Consumer %d consumed in slot %d! %d  widgets left!\n",
           tid, temp, shared_factory->widget_count);

}

//*************************************************************
//*************************************************************
// Displays user input menu
//*************************************************************
//*************************************************************
void printMenu() {
    std::cout << "\nPlease enter which test trial you wish to run: \n";
    std::cout << "1) Run Producer and Consumer as Functions\n";
    std::cout << "2) Spawn a Producer and Consumer as Threads\n";
    std::cout << "3) Spawn 5 Producer and 5 Consumer Threads\n";
    std::cout << "\n9) End Tests\n";
    std::cout << "\nYour selection please: ";
}
