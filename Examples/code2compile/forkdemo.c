#include <stdlib.h>     // exit()
#include <stdio.h>      // printf()
#include <unistd.h>     // fork(), wait(), sleep(), pid_t

int main()
{
   int processStat = 0;
   printf("Parent: Welcome to a Forking Demo!\n");
   
   // Create a process
   pid_t childPID = fork();
   if (childPID == 0)
   {
      //  This is the child
      printf("Child: Greetings Tim, I am going to sleep ...\n");
      sleep(10);
      printf(" ... now awake after 10 seconds.  Bye\n");
   }
   else
   {
      // Wait for the child to terminate
      printf("Parent: Waiting ...\n");
      pid_t thisChildPID = wait(&processStat);
      printf("Parent: Child terminated\n");
      exit(0);
   }
}

