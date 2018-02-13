#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
/* buffer.h*/

typedef int buffer_item;
#define BUFFER_SIZE 5

void* producer(void* param);
void* consumer(void* param);
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertLocation = 0;
int removeLocation = 0;


int main(int argc, char* argv[])
{
	int i = 0;
	int j = 0;

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <simulation time> <producer threads> <consumer threads>\n");
		return -1;
	}

	int sleepTime = atoi(argv[1]);
	int producerThreads = atoi(argv[2]);
	int consumerThreads = atoi(argv[3]);

	//Initialize the the locks
	printf("Initializing locks . . .\n");
	printf("mutex returned %d\n",pthread_mutex_init(&mutex, NULL));
	printf("empty returned %d\n",sem_init(&empty, 0, 5));
	printf("full returned %d\n",sem_init(&full, 0, 0));

	//Create the producer and consumer threads
	for(i = 0; i < producerThreads; i++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, NULL);
	}

	//Sleep for user specified time
	sleep(sleepTime);
	return 0;
}

void* producer(void* param)
{
	buffer_item random;
	int r;

	while(TRUE)
	{
		r = rand() % 5;
		sleep(r);
		random = rand();

		if(insert_item(random))
			fprintf(stderr, "Error");

		printf("Producer produced %d \n", random);

	}
}

int insert_item(buffer_item item)
{
    //Acquire Empty Semaphore
	sem_wait(&empty);
	
	//Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	buffer[insertLocation++] = item;
	insertLocation = insertLocation % 5;

	//Release mutex lock and full semaphore
	pthread_mutex_unlock(&mutex);
    sem_post(&full);

	return 0;
}

void* consumer(void* param)
{
	buffer_item random;
	int r;

	while(TRUE)
	{
		r = rand() % 5;
		sleep(r);

		if(remove_item(&random))
			fprintf(stderr, "Error Consuming");
		else
			printf("Consumer consumed %d \n", random);
	}
}

int remove_item(buffer_item* item)
{
	//Acquire Full Semaphore
	sem_wait(&full);

	//Acquire mutex lock to protect buffer
	pthread_mutex_lock(&mutex);
	*item = buffer[removeLocation];
	buffer[removeLocation++] = -1;
	removeLocation = removeLocation % 5;

	//Release mutex lock and empty semaphore
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	return 0;
}

