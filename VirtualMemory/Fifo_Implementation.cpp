//
// Created by michael on 2/7/18.
//

#include "Fifo_Implementation.h"

/*
 * Constructor
 */
Fifo_Implementation::Fifo_Implementation(Virtual_Memory *virtual_memory) : Physical_Memory(virtual_memory) {
    // Initialize variables
    this->algorithm_name = "FIFO";
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
void Fifo_Implementation::place_pointer(int current_position) {
    // Logic for this page replacement algorithm
    ram_pointer = (++ram_pointer) % num_frames;
}
