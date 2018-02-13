//
// Created by michael on 2/7/18.
//

#include "Physical_Memory.h"
#include "Virtual_Memory.h"

#ifndef VIRTUALMEMORY_LFU_IMPLEMENTATION_H
#define VIRTUALMEMORY_LFU_IMPLEMENTATION_H


class Lfu_Implementation : public Physical_Memory {

private:
    int starting_frame;
    int least_frequent_frame_frequency;
    int least_frequent_frame;

public:
    // Constructor
    Lfu_Implementation(Virtual_Memory *virtual_memory);

public:
    // Public Methods
    void place_pointer(int current_position);
};


#endif //VIRTUALMEMORY_LFU_IMPLEMENTATION_H
