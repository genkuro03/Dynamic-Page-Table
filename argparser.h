/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <iostream>
#include <string>
#include "pagetabledefinition.h"

class ArgParser {

public:
    ArgParser(int argc, char* argv[]);
    ~ArgParser();

    PageTableDefinition* pageTableDefinition;
    char* fileName;
    int numLevels;
    int *levelSizes;

private:
    void error(char* program_name, bool showUsage, bool shouldExit, const std::string& message);
    void pulloutIntegers(char* argv[]);
};



#endif //ARGPARSER_H
