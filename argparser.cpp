/*Ethan Fox
*CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#include "argparser.h"
#include "pagetabledefinition.h"
#include <iostream>
#include <cstring>

ArgParser::ArgParser(int argc, char* argv[]) {

    //Checks if 3 arguments (ex   ./pageTrace trace.tr "4 4 4")   )
    if (argc != 3) {
        fileName = nullptr;     //Throws error if not 3
        error(argv[0], true, true, std::string("Wrong number of arguments."));
    }

    this->fileName = new char[strlen(argv[1]) + 1]; //allocate memory to store filename (so we don't rely on argv[2] pointer
    strcpy(fileName, argv[1]);  //copy the string to new memory address

    //Helper function to extract the information required from the cmd line
    //Will convert ./pageTrace trace.tr "4 4 4" into
    //numLevels -> 3, levelSizes = [4,4,4]...
    pulloutIntegers(argv);


    this->pageTableDefinition = new PageTableDefinition(numLevels, levelSizes); //Calls pageTableDefinition constructor (metadata of pageTable)
}


ArgParser::~ArgParser() {   //Deconstructor
    delete this->pageTableDefinition;
    delete this->fileName;
}

void ArgParser::pulloutIntegers(char* argv[]) {

    char* program_name = argv[0];   //Stores program name (./pageTrace)
    char* strDefinition = argv[2];  //Stores pageSizes str "4 4 4"

    //temp array to store level sizes
    //set to 32 in case 32 pages of 1 bit each...
    int tempLevelSizes[32];

    numLevels = 0;

    int defStringIndex = 0; //range of chars in argv[2]
    int last = strlen(strDefinition) - 1;

    //skip quotes if they exist
    if (strDefinition[defStringIndex] == '\"') {
        defStringIndex += 1;
    }
    if (strDefinition[last] == '\"') {
        last -= 1;
    }

    int nextValue = -1; //"Finder of ints"

    //nextIndex shows where we are in the argv[2]
    int nextIndex = 0;
    for ( ; defStringIndex <= last; defStringIndex++) {
        char n = strDefinition[defStringIndex];
        if (isdigit(n)) {
            if (nextValue == -1) {
                //new number
                nextValue = n - '0';
            }
            else {
                //part of a double digit numbre
                nextValue = nextValue * 10 + n - '0';
            }
        }
        else if (isspace(n)) {
            //space,  So if we see a space, we got the whole number
            if (nextValue > 0) {
                tempLevelSizes[nextIndex++] = nextValue;
                numLevels++;
                nextValue = -1;
            }
        }
        else {
            //we got some other illegal character
            error(program_name, true, true, "Invalid character in pagetable definition");
            break;
        }
    }

    //Finished looping, grabs the final numbre (no space at end)
    if (nextValue > 0) {
        tempLevelSizes[nextIndex++] = nextValue;
        nextValue = -1;
        numLevels++;
    }

    if (numLevels <= 0) { //Empty argv[2]
        error(program_name, true, true, "Empty pagetable definition");
    }

    for (int i=0; i < numLevels; i++) { //If any page size is greater than 32 bit system
        if (tempLevelSizes[i] > 32) {
            error(program_name, true, true, "Bit overflow in pagetable definition");
        }
    }

    levelSizes = new int[numLevels];    //Creates proper fitting array with levelSizes pointer
    for (int i=0; i < numLevels; i++) { //Copies data from temp -> field
        levelSizes[i] = tempLevelSizes[i];
    }
    //tempLevelSizes should deallocate since out of local scope... saving space, yay!
}


//Prints out usage along with an error message, exits conditionally on parameter
void ArgParser::error(char* program_name, bool showUsage, bool shouldExit, const std::string& message) {
    std::cerr << "Error: " << message << std::endl;

    if (showUsage) {
        std::cerr << "Usage:   " << program_name << " <filename> \"<page description>\"" << std::endl;
        std::cerr << "Example: " << program_name << " MyFile \"4 4 3\"" << std::endl;
    }
    if (shouldExit) {
        std::exit(-1);
    }
}



