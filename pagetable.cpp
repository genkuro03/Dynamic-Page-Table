/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#include "pagetable.h"
#include "pagetabledefinition.h"
#include "pagelevel.h"

PageTable::PageTable(PageTableDefinition* definition) {
    this->tableDefinition = new PageTableDefinition(*definition);   //Creates a deep copy of pageTable ensuring its own addresses and variables
    this->root = new Level(definition, 0);  //Creates level 0 initially
}

PageTable::~PageTable() {   //Deconstructor
    if (tableDefinition != nullptr) {
        delete this->tableDefinition;
    }
}


void PageTable::recordAccess(unsigned int address) {    //Record access, adds addresses, expands levels
    root->recordAccess(address);    //calls other .cpp files to act as helper functions
}


