//
// Created by michael on 2/7/18.
//

#include "Lfu_Implementation.h"

Lfu_Implementation::Lfu_Implementation(Virtual_Memory *virtual_memory) : Physical_Memory(virtual_memory) {
    // Initialize variables
    this->algorithm_name = "LFU";
    for(int i = 0; i < MAX_FRAMES; i++) {
        this->ram_memory[i] = -1;
        this->frame_counter[i] = -1;
        this->frame_history[i] = "";
    }
    this->num_frames = 0;
    this->ram_pointer = 0;
    this->page_faults = 0;
    this->already_in_memory = false;
    this->starting_frame = 0;
    this->least_frequent_frame = 0;
    this->least_frequent_frame_frequency = 1;

    // Get number of page frames from the user
    get_number_of_page_frames();
}

/*
 * Public Methods
 */
void Lfu_Implementation::place_pointer(int current_position) {
    // Handle out-of-sync starting frames
    if(frame_counter[starting_frame] != least_frequent_frame_frequency) {
        // Reset the least frequent frame frequency to the updated value
        least_frequent_frame_frequency = frame_counter[starting_frame];
        // Loop through the starting position to fall-back on a FIFO like swapping pattern
        do {
            starting_frame = (++starting_frame) % num_frames;
        } while(frame_counter[starting_frame] > least_frequent_frame_frequency);
    }

    // If the count is less than the current smallest then set the new smallest frequency
    least_frequent_frame = starting_frame;
    least_frequent_frame_frequency = frame_counter[starting_frame];

    // For each frame
    for(int i = starting_frame; ; i++) {
        // If the index is greater than the number of frames
        if(i >= num_frames) {
            // Break the endless for-loop
            break;
        }

        // If there is a frame being used less frequently
        if(frame_counter[i] < frame_counter[least_frequent_frame]) {
            // Update the least frequent frame
            least_frequent_frame = i;
            least_frequent_frame_frequency = frame_counter[i];
            // Break the endless for-loop
            break;
        }
    }

    // Reset frame counter
    frame_counter[least_frequent_frame] = 1;

    // Set ram pointer to least frequently occurring frame value
    ram_pointer = least_frequent_frame;

    // Loop through the starting position to fall-back on a FIFO like swapping pattern
    do {
        starting_frame = (++starting_frame) % num_frames;
    } while(frame_counter[starting_frame] > least_frequent_frame_frequency);

    // Note the least frequent frame frequency for testing later
    least_frequent_frame_frequency = frame_counter[starting_frame];
}
