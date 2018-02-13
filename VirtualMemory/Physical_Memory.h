//
// Created by michael on 2/7/18.
//

#include <string>
#include "Virtual_Memory.h"

#define MIN_FRAMES 2
#define MAX_FRAMES 7
#define ADDRESS_QUANTITY 100

#ifndef VIRTUALMEMORY_Physical_Memory_H
#define VIRTUALMEMORY_Physical_Memory_H


class Physical_Memory {

protected:
    // State
    Virtual_Memory *virtual_memory;
    std::string algorithm_name;
    int ram_memory[MAX_FRAMES];
    int num_frames;
    int ram_pointer;
    int page_faults;
    int frame_counter[MAX_FRAMES];
    bool already_in_memory;
    std::string frame_history[MAX_FRAMES];

protected:
    // Helper Methods
    virtual void place_pointer(int current_position) = 0;
    void get_number_of_page_frames();
    void add_frame_history();

public:
    // Constructor
    Physical_Memory(Virtual_Memory *virtual_memory);

public:
    // Getters
    int getPage_faults() const;
    int getNum_frames() const;

public:
    // Public Methods
    void run();
    void display_stats();

};


#endif //VIRTUALMEMORY_Physical_Memory_H
