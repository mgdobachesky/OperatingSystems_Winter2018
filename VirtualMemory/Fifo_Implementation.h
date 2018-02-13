//
// Created by michael on 2/7/18.
//

#include "Physical_Memory.h"
#include "Virtual_Memory.h"

#ifndef VIRTUALMEMORY_FIFO_IMPLEMENTATION_H
#define VIRTUALMEMORY_FIFO_IMPLEMENTATION_H


class Fifo_Implementation : public Physical_Memory {

public:
    // Constructor
    Fifo_Implementation(Virtual_Memory *virtual_memory);

public:
    // Public Methods
    void place_pointer(int current_position);

};


#endif //VIRTUALMEMORY_FIFO_IMPLEMENTATION_H
