//
// Created by michael on 2/7/18.
//
#include <iostream>
#include "Virtual_Memory.h"


/*
 * Constructor
 */
Virtual_Memory::Virtual_Memory() {
    // Initialize variables
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        address_buffer[i] = 0;
        address_page[i] = 0;
        address_offset[i] = 0;
    }

    // Generate virtual addresses
    generate_addresses();

    // Translate virtual addresses
    translate_addresses();
}


/*
 * Getters
 */

const unsigned short *Virtual_Memory::getAddress_buffer() const {
    return address_buffer;
}

const unsigned short *Virtual_Memory::getAddress_page() const {
    return address_page;
}

const unsigned short *Virtual_Memory::getAddress_offset() const {
    return address_offset;
}

short Virtual_Memory::getAddress_quantity() {
    return ADDRESS_QUANTITY;
}


/*
 * Helper Methods
 */
void Virtual_Memory::generate_addresses() {
    // Initialize variables
    unsigned short random_virtual_address = 0;

    // Seed random numbers
    srand(time(NULL));

    // Generate a virtual address i times
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        // Generate random virtual address and put it in array
        random_virtual_address = rand();
        address_buffer[i] = random_virtual_address;
    }
}

void Virtual_Memory::translate_addresses() {
    for(int i = 0; i < ADDRESS_QUANTITY; i++) {
        // Extract the virtual address page and offset
        address_page[i] = address_buffer[i] >> 12;
        address_offset[i] = address_buffer[i] << 4;
        address_offset[i] = address_offset[i] >> 4;
    }
}
