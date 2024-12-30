/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#ifndef PAGETABLEDEFINITION_H
#define PAGETABLEDEFINITION_H


// A relatively small description of a PageTable.  This contains everything to
// manage a PageTable tree.
class PageTableDefinition {

public:
    // ex: numLevels = 3 and levelSizes = {8,4,4}
    PageTableDefinition(int numLevels, const int* levelSizes);
    ~PageTableDefinition();

    // copy constructor
    PageTableDefinition(const PageTableDefinition& other);
    // assignment operator
    PageTableDefinition& operator=(const PageTableDefinition& other);

    unsigned int* bitMaskArray;
    int* shiftArray;
    int* bitsUsed;
    int numLevels{};
};

#endif //PAGETABLEDEFINITION_H
