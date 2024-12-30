/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#ifndef PAGETABLE_H
#define PAGETABLE_H

#include "pagetabledefinition.h"
#include "pagelevel.h"

class PageTable {

public:
    PageTable(PageTableDefinition* definition);
    ~PageTable();
    void recordAccess(unsigned int address);

private:
    PageTableDefinition* tableDefinition;
    Level* root;
};



#endif //PAGETABLE_H
