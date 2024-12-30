/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#ifndef LEVEL_H
#define LEVEL_H

#include "pagetabledefinition.h"

class Level {

public:
    Level(PageTableDefinition *definition, int depth);
    ~Level();
    void recordAccess(unsigned int address);
    int extractPageNumberFromAddress(unsigned int address, unsigned int mask, int shift);

private:

    // We keep a common reference to the table definition.
    PageTableDefinition* tableDefition;

    // This helps us construct this object so that it knows its place in the
    // table.  bitsUsed will define the size of the children array.  That is,
    // we'll have 2^bitsUsed children.
    int myDepth;
    int bitsUsed;

    // These variables are used to scrape off the interesting bits.  We
    // bitwise-and with the mask then shift to the right to get a normalized
    // number.
    unsigned int mask;
    int shift;

    // All the children ..
    Level** nextLevels;

    // Metrics
    // This is the important one in terms of the assignment
    int numAccesses;

};



#endif //LEVEL_H
