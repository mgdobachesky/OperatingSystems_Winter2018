#include <stdio.h>
#include "mythreads.h"
#include <stdlib.h>
#include <pthread.h>

int max;
volatile int counter = 0; // shared global variable

void* mythread(void* arg)
{
   char* letter = arg;
   int i; // stack (private per thread) 
   printf("%s: begin [addr of i: %p]\n", letter, &i);

   for (i = 0; i < max; i++)
   {
      counter = counter + 1; // shared: only one
   }
   
   printf("%s: done\n", letter);
   return NULL;
}
                                                                             
int main(int argc, char* argv[])
{                    
   pthread_t p1, p2;
   
   if (argc != 2)
   {
      fprintf(stderr, "usage: main-first <loopcount>\n");
      exit(1);
   }
   max = atoi(argv[1]);
   
   // Launch threads
   printf("main: begin [counter = %d] [%x]\n", counter, &counter);
   pthread_create(&p1, NULL, mythread, "A");
   pthread_create(&p2, NULL, mythread, "B");
   
   // join waits for the threads to finish
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   
   printf("main: done\n [counter: %d]\n [should: %d]\n", counter, max*2);
   return 0;
}

