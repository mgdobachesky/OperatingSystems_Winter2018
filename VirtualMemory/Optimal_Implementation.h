//
// Created by michael on 2/8/18.
//

#include "Physical_Memory.h"
#include "Virtual_Memory.h"

#ifndef VIRTUALMEMORY_OPTIMAL_IMPLEMENTATION_H
#define VIRTUALMEMORY_OPTIMAL_IMPLEMENTATION_H


class Optimal_Implementation  : public Physical_Memory {
public:
    // Constructor
    Optimal_Implementation(Virtual_Memory *virtual_memory);

public:
    // Public Methods
    void place_pointer(int current_position);

};


#endif //VIRTUALMEMORY_OPTIMAL_IMPLEMENTATION_H
