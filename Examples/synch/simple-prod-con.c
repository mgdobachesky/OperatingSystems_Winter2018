/**
 * Simple program demonstrating shared memory in POSIX systems.
 * Producer - Consumer Battle 
*/

#include <signal.h> 
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

// Number of widget slots
#define BUFFER_SIZE 200

// Seconds to run factory simulation
#define SIM_LENGTH 20

int main()
{
	int producer_id;
	int consumer_id;

	/* Structure to hold shared data */
	typedef struct {
		int next_in;
		int next_out;
		int widget_count;
		int buffer[BUFFER_SIZE];
	} widget_factory_t;
	
	/* the identifier for the shared memory segment */
	int segment_id;
	/* a pointer to the shared memory segment */
	widget_factory_t* shared_factory;
	/* the size (in bytes) of the shared memory segment */ 
	const int segment_size = sizeof(widget_factory_t);

	/** allocate  a shared memory segment */
	segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

	/** attach the shared memory segment */
	shared_factory = (widget_factory_t *) shmat(segment_id, NULL, 0);
	printf("shared memory segment %d attached at address %p\n", segment_id, shared_factory);
	
	/* Initialize Widget Factory */
	shared_factory->next_in = 0;
	shared_factory->next_out = 0;
	shared_factory->widget_count = 0;

	/* fork a child to produce */
	if ( (producer_id = fork()) == 0) {
		while(1) { //loop until death
			while (shared_factory->widget_count == BUFFER_SIZE) ;
			//sleep(1);
			/* There's a free slot, so we produce a widget */
			shared_factory->buffer[++(shared_factory->widget_count)] = rand();
			shared_factory->next_in = (shared_factory->next_in + 1) % BUFFER_SIZE;
			printf("Producer produced! %d widgets now available!\n",shared_factory->widget_count);
		}
	} 
	/* fork a process to consume widgets */
	else if ( (consumer_id = fork()) == 0) {
		while(1) { //loop until death
			while (shared_factory->widget_count == 0) ;
			//sleep(2);
			/* There's a widget available slot, so we consume widget */
			int eat_widget = shared_factory->buffer[(shared_factory->widget_count)--];
			shared_factory->next_out = (shared_factory->next_out + 1) % BUFFER_SIZE;
			printf("***** Consumer consumed  %d  widgets left!\n",shared_factory->widget_count);
		}
	} else
	/* parent to time simulation */
		printf("Parent sleeping for %d seconds to let simulation run \n", SIM_LENGTH);
		sleep(SIM_LENGTH);
		/* kill producer */
		producer_id = kill(producer_id, SIGKILL);
		/* kill consumer */
		consumer_id = kill(consumer_id, SIGKILL);
		printf("Parent killed both children!\n");
	/** now detach the shared memory segment */ 
	if ( shmdt(shared_factory) == -1) {
		fprintf(stderr, "Unable to detach\n");
	}

	/** now remove the shared memory segment */
	shmctl(segment_id, IPC_RMID, NULL); 

	return 0;
}
