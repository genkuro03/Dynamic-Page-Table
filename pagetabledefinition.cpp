/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#include <iostream>

#include "pagetabledefinition.h"



PageTableDefinition::PageTableDefinition(int numLevels, const int* levelSizes) { //Will get info from argparser.cpp

    this->bitMaskArray = new unsigned int[numLevels]; //Fills out fields / allocate memory
    this->shiftArray = new int[numLevels];
    this->bitsUsed = new int[numLevels];
    this->numLevels = numLevels;

    int currentBitsUsed = 0;    //Keep track of how many bits used

    for (int i=0; i < numLevels; i++) {
        bitsUsed[i] = levelSizes[i];    //Translates arguments into fields
        int levelBits = levelSizes[i];  //temp value to store bits (for later conversion)

        int shift = 32 - levelBits - currentBitsUsed;   //32 - level 0, 32 - (lvl 0 + lvl 1)...
        unsigned int mask = ~0;   //bitwise operation to make 111... mask
        mask = mask >> (32 - levelBits);  //shift excess 1s off
        mask = mask << shift;  // shift back to get right placement

        shiftArray[i] = shift;  //Stores shift for each page in proper position
        bitMaskArray[i] = mask; //Stores newly made mask for each page
        currentBitsUsed += levelBits;   //Calculates total bits used for later calc (part of line 18)
    }

    int bitsLeft = 32 - currentBitsUsed;    //Makes a final mask for the remaining bits (if there are any)
    unsigned int mask = 0;
    for (int j=0; j < bitsLeft; j++) {
        mask = (mask << 1) + 1;
    }
    bitMaskArray[numLevels] = mask;
    shiftArray[numLevels] = 0;
}


PageTableDefinition::~PageTableDefinition() {
    //Release dynamically allocated memory
    delete[] bitMaskArray;
    delete[] shiftArray;
}




PageTableDefinition::PageTableDefinition(const PageTableDefinition& other) {    //Deep copy constructor to combine data
    numLevels = other.numLevels;

    if (other.bitMaskArray) {
        bitMaskArray = new unsigned int[numLevels];
        std::copy(other.bitMaskArray, other.bitMaskArray + numLevels, bitMaskArray);
    } else {
        bitMaskArray = nullptr;
    }

    if (other.shiftArray) {
        shiftArray = new int[numLevels];
        std::copy(other.shiftArray, other.shiftArray + numLevels, shiftArray);
    } else {
        shiftArray = nullptr;
    }
}


PageTableDefinition& PageTableDefinition::operator=(const PageTableDefinition& other) { //overwrites = operator to allow for pageTable transfer
    if (this == &other) return *this;  //Self-assignment check

    delete[] bitMaskArray;
    delete[] shiftArray;

    numLevels = other.numLevels;

    if (other.bitMaskArray) {
        bitMaskArray = new unsigned int[numLevels];
        std::copy(other.bitMaskArray, other.bitMaskArray + numLevels, bitMaskArray);
    } else {
        bitMaskArray = nullptr;
    }

    if (other.shiftArray) {
        shiftArray = new int[numLevels];
        std::copy(other.shiftArray, other.shiftArray + numLevels, shiftArray);
    } else {
        shiftArray = nullptr;
    }

    return *this;
}




