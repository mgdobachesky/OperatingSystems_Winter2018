#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int main() {
   int processStat = 0;
   printf("Parent: Welcome to a Forking Demo!\n");
   
   // Create a process
   pid_t childPID = fork();
   if (childPID == 0)
   {
      pid_t myID1 = getpid(); //  This is the child
      printf("Child1 %d: Greetings Tim, I am going to sleep ...\n",myID1);
      sleep(10);
      printf("Child1 %d:  ... now awake after 10 seconds.  Bye\n", myID1);
   }
   else if ((childPID = fork()) == 0)
   {
      pid_t myID2 = getpid();
      printf("Child2 %d: Hey there - going to sleep for 5!\n", myID2);
      sleep(5); 
      printf("Child2 %d:  ... now awake after 5 seconds. Later!\n", myID2); 
   } 
   else
   {
   
      // Wait for the child to terminate
      printf("Parent: Waiting ...\n");
      pid_t thisChildPID = wait(&processStat);
      printf("Parent: %d Child terminated\n", thisChildPID);
      exit(0);
   }
}

