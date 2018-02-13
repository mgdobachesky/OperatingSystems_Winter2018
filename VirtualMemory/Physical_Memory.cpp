//
// Created by michael on 2/7/18.
//

#include <iostream>
#include <fstream>
#include "Physical_Memory.h"


/*
 * Constructor
 */
Physical_Memory::Physical_Memory(Virtual_Memory *virtual_memory) {
    // Set Virtual Memory
    this->virtual_memory = virtual_memory;

    // Initialize Variables
    for(int i = 0; i < MAX_FRAMES; i++) {
        this->ram_memory[i] = -1;
        this->frame_counter[i] = -1;
        this->frame_history[i] = "";
    }
    this->num_frames = 0;
    this->ram_pointer = 0;
    this->page_faults = 0;
    this->already_in_memory = false;
}


/*
 * Getters
 */
int Physical_Memory::getPage_faults() const {
    return page_faults;
}

int Physical_Memory::getNum_frames() const {
    return num_frames;
}


/*
 * Public Methods
 */
void Physical_Memory::run() {
    // Load every page into memory frames
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        // Check each frame to see if the value is already in memory
        for(int j = 0; j < num_frames; j++) {
            if(ram_memory[j] == virtual_memory->getAddress_page()[i]) {
                // Handle no need to re-load a page
                already_in_memory = true;

                // Increment sequential frames counter
                ++frame_counter[j];

                // Break out of the frames loop
                break;
            } else if(ram_memory[j] == -1) {
                // Handle empty frames
                ram_pointer = j;
                ram_memory[ram_pointer] = virtual_memory->getAddress_page()[i];
                already_in_memory = true;

                // Initialize sequential frames counter
                frame_counter[j] = 1;

                // Increment the page fault counter
                ++page_faults;

                // Break out of the frames loop
                break;
            } else {
                // Handle page faults
                already_in_memory = false;
            }
        }

        // If the value is not already in memory then load it in
        if(!already_in_memory) {
            // Run the specific page replacement algorithm to position the pointer
            place_pointer(i);

            // Load current page into available frame
            ram_memory[ram_pointer] = virtual_memory->getAddress_page()[i];

            // Increment the page fault counter
            ++page_faults;
        }

        // Add a time tick to the frame history
        add_frame_history();
    }
}

void Physical_Memory::display_stats() {
    // Initialize variables
    std::fstream output_file;
    std::string line;
    std::string separator;
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        separator.append("--\t");
    }

    // Notify user that writing has started
    std::cout << "Writing to file: " << algorithm_name << "..." << std::endl;

    // Open the file in write mode
    output_file.open(algorithm_name, std::fstream::out);
    // Record the amount of page faults incurred during this page replacement algorithm
    output_file << algorithm_name << " Page Faults: " << page_faults << std::endl << std::endl;
    // Close the file in write mode
    output_file.close();

    // Open the file in append mode
    output_file.open(algorithm_name, std::fstream::app);
    // Print the original page buffer
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        output_file << virtual_memory->getAddress_page()[i] << "\t";
    }
    // Print a separator between the original buffer and results
    output_file << std::endl << separator << std::endl;
    // Print out each frame's history
    for(int i = 0; i < num_frames; i++) {
        // Append this frame to the file
        output_file << frame_history[i] << std::endl;
    }
    // Append and extra carriage return at the end
    output_file << std::endl;
    // Close the file in append mode
    output_file.close();

    // Notify user that writing has finished
    std::cout << "...Finished writing to file: " << algorithm_name << std::endl << std::endl;

    // Open the file in read mode
    output_file.open(algorithm_name, std::fstream::in);
    // Print the contents to the console
    if(output_file.is_open()) {
        while(getline(output_file, line)) {
            std::cout << line << std::endl;
        }
    }
    // Close the file in read mode
    output_file.close();
}

/*
 * Helper Methods
 */
void Physical_Memory::get_number_of_page_frames() {
    // Prompt the user for the number of page frames
    std::cout << "How many page frames do you want to use for the " << algorithm_name << " algorithm?";
    std::cout << " (between " << MIN_FRAMES << " and " << MAX_FRAMES << ")" << std::endl;
    std::cin >> num_frames;
    std::cout << std::endl;

    // Make sure number of frames is between 2 and 7
    while(num_frames < MIN_FRAMES || num_frames > MAX_FRAMES) {
        std::cout << "Number of page frames must be between " << MIN_FRAMES << " and " << MAX_FRAMES << std::endl;
        std::cin >> num_frames;
        std::cout << std::endl;
    }
}

void Physical_Memory::add_frame_history() {
    // Add the frame onto the frame history for display
    for(int i = 0; i < num_frames; i++) {
        // For every frame
        if(i != ram_pointer) {
            // If the current iteration is not the location of the ram pointer
            if(ram_memory[i] == -1) {
                // If the frame is empty then append a blank tab
                frame_history[i].append("\t");
            } else {
                // Else append the current frame
                frame_history[i].append(std::to_string(ram_memory[i]) + "\t");
            }
        } else if(i == ram_pointer) {
            // If the current iteration is the location of the ram pointer
            // Append to the frame history the current frame
            frame_history[ram_pointer].append(std::to_string(ram_memory[ram_pointer]) + "\t");
        }
    }

}