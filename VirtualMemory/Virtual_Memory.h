//
// Created by michael on 2/7/18.
//

#ifndef VIRTUALMEMORY_VIRTUAL_MEMORY_H
#define VIRTUALMEMORY_VIRTUAL_MEMORY_H
#define ADDRESS_QUANTITY 100


class Virtual_Memory {

private:
    // State
    unsigned short address_buffer[ADDRESS_QUANTITY];
    unsigned short address_page[ADDRESS_QUANTITY];
    unsigned short address_offset[ADDRESS_QUANTITY];

private:
    // Helper Methods
    void translate_addresses();
    void generate_addresses();

public:
    // Constructor
    Virtual_Memory();

public:
    // Getters
    const unsigned short *getAddress_buffer() const;
    const unsigned short *getAddress_page() const;
    const unsigned short *getAddress_offset() const;
    short getAddress_quantity();

};


#endif //VIRTUALMEMORY_VIRTUAL_MEMORY_H
