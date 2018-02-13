#include <iostream>
#include "Virtual_Memory.h"
#include "Physical_Memory.h"
#include "Fifo_Implementation.h"
#include "Lfu_Implementation.h"
#include "Optimal_Implementation.h"

/*
 * Main program driver
 */
int main() {
    // Initialize variables
    int exit_switch = 0;
    int algorithm_choice = 0;

    // Create some virtual memory
    Virtual_Memory* virtual_memory = new Virtual_Memory();

    // Create some physical memory
    Physical_Memory* physical_memory;

    do {
        // Prompt the user to make an algorithm choice and store his/her decision
        std::cout << "Choose an algorithm to use while implementing physical memory: " << std::endl;
        std::cout << "1): FIFO " << std::endl;
        std::cout << "2): LFU " << std::endl;
        std::cout << "3): Optimal " << std::endl;
        std::cout << "0): Exit " << std::endl;
        std::cin >> algorithm_choice;
        std::cout << std::endl;

        switch(algorithm_choice) {
            case 1:
                // Create an instance of physical memory with the FIFO page replacement algorithm
                physical_memory = new Fifo_Implementation(virtual_memory);
                // Back to main menu
                break;
            case 2:
                // Create an instance of physical memory with the LFU page replacement algorithm
                physical_memory = new Lfu_Implementation(virtual_memory);
                // Back to main menu
                break;
            case 3:
                // Create an instance of physical memory with the Optimal page replacement algorithm
                physical_memory = new Optimal_Implementation(virtual_memory);
                // Back to main menu
                break;
            case 0:
                // Turn on the exit switch
                exit_switch = 1;
        }

        // Check if the user wants to exit the program
        if(exit_switch == 1) {
            // Exit if the user requests to do so
            break;
        }

        // Run the various page replacement algorithms
        physical_memory->run();
        // Display state for the various page replacement algorithms
        physical_memory->display_stats();

    } while(true);

    // Exit successfully
    return 0;
}