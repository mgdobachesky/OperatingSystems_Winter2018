/**
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int sum = 0; /* this data is shared by the thread(s) */

void* sumFunction(void* param); /* the thread */

int main(int argc, char* argv[])
{
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	
	if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}
	
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
		return -1;
	}
	
	/* get the default attributes */
	pthread_attr_init(&attr);
	
	/* create the thread */
	pthread_create(&tid, &attr, sumFunction, argv[1]);
   
   printf("I am the parent thread and I'm waiting. \n");
	
	/* now wait for the thread to exit */
	pthread_join(tid,NULL);
	
   printf("I am the parent thread and the child finished. \n");

	printf("Shared variable Sum = %d\n",sum);
}

/**
 * The thread will begin control in this function
 */
void* sumFunction(void *param)
{
   printf("I am the child thread and I'm working. \n");
	int i = 0;
        int upper = atoi(param);
	sum = 0;
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	pthread_exit(0);
}

