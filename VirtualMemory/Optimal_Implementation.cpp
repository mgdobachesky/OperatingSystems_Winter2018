//
// Created by michael on 2/8/18.
//

#include <iostream>
#include "Optimal_Implementation.h"

Optimal_Implementation::Optimal_Implementation(Virtual_Memory *virtual_memory) : Physical_Memory(virtual_memory) {
    // Initialize variables
    this->algorithm_name = "Optimal";
    for(int i = 0; i < MAX_FRAMES; i++) {
        this->ram_memory[i] = -1;
        this->frame_counter[i] = -1;
        this->frame_history[i] = "";
    }
    this->num_frames = 0;
    this->ram_pointer = 0;
    this->page_faults = 0;
    this->already_in_memory = false;

    // Get number of page frames from the user
    get_number_of_page_frames();
}


/*
 * Public Methods
 */
void Optimal_Implementation::place_pointer(int current_position) {
    // Initialize variables
    int maximum_distance = 0;
    for(int i = 0; i < num_frames; i++) {
        frame_counter[i] = -1;
    }
    
    // Logic for this page replacement algorithm
    // For every frame
    for(int i = 0; i < num_frames; i++) {
        // For every page in virtual memory after the current position
        for(int j = current_position; j < virtual_memory->getAddress_quantity(); j++) {
            // If a match is found
            if(ram_memory[i] == virtual_memory->getAddress_page()[j]) {
                // Record matches distance from the current position
                frame_counter[i] = j - current_position;

                // Break out of the for loop early
                break;
            }
            // If we have reached the end of the page buffer
            if(j + current_position + 1 == virtual_memory->getAddress_quantity()) {
                // Mark this frame as available
                frame_counter[i] = -1;
            }
        }
    }
    
    // Determine the largest frame
    for(int i = 0; i < num_frames; i++) {
        // For each frame
        if(frame_counter[i] == -1) {
            // If the value in the frame will not be used again place the pointer there
            ram_pointer = i;

            // Break out of the for loop early
            break;
        }

        // Find the address of the frame with the maximum distance
        if(frame_counter[i] > maximum_distance) {
            // Set the new maximum distance
            maximum_distance = frame_counter[i];

            // Set ram pointer to the new furthest distance
            ram_pointer = i;
        }
    }
}