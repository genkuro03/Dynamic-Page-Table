/*Ethan Fox
 *CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#include "pagelevel.h"

#include <iomanip>
#include <iostream>

#include "log.h"

int Level::extractPageNumberFromAddress(unsigned int address, unsigned int mask, int shift){
    return (address & mask) >> shift;
}

Level::Level(PageTableDefinition *definition, int depth) {

    this->tableDefition = definition;
    this->myDepth = depth;
    this->numAccesses = 0;

    //Grabs definition info for local scope
    this->mask = definition->bitMaskArray[depth];
    this->shift = definition->shiftArray[depth];
    this->bitsUsed = definition->bitsUsed[depth];

    //Used to keep track of child nodes by using bitwise operators
    int childCount = 1 << bitsUsed;

    //expanding trees
    this->nextLevels = new Level*[childCount];

    //Initialize every variable as nullptr
    for (int i=0; i < childCount; i++) {
        nextLevels[i] = nullptr;
    }
}


Level::~Level() { //deconstructor....
}



void Level::recordAccess(unsigned int address) {    //Record accesses for each address
    numAccesses += 1;       //Increments access count by one at each level it passes
    if (myDepth < tableDefition->numLevels) {   //Checks if at final page
        //int index = (address & mask) >> shift;
        int index = extractPageNumberFromAddress(address, mask, shift);//Continues to shift and mask to find proper position in level array

        if (nextLevels[index] == nullptr) {     //Creates new Level if none exists (first instance)
            nextLevels[index] = new Level(tableDefition, myDepth + 1);
        }
        nextLevels[index]->recordAccess(address);   //If instance exists, follow through pointer
    }
    else {
        unsigned int pageIndices[tableDefition->numLevels]; //Case scenario that at end of tree
        for (int i=0; i < tableDefition->numLevels; i++) {  //logs the numOfAccesses
            unsigned int _mask = tableDefition->bitMaskArray[i];
            unsigned int _shift = tableDefition->shiftArray[i];
            pageIndices[i] = (address & _mask) >> _shift;
        }
        log_pgindices_numofaccesses(address, tableDefition->numLevels, pageIndices, numAccesses);
    }
}