/*Ethan Fox
 *CS 480 - Operating Systems
 *Ben Shen
 *9/9/2024
 *REDID = 826136708*/

#include <iostream>

#include "pagetable.h"
#include "argparser.h"
#include "log.h"
#include "tracereader.h"


int main(int argc, char* argv[]) {

    //Helper function to help extract the information from argv[],
    //Use later to help fill out pageTableDefinition
    ArgParser args(argc, argv);

    PageTable table(args.pageTableDefinition);

    log_bitmasks(args.pageTableDefinition->numLevels, args.pageTableDefinition->bitMaskArray);

    p2AddrTr mtrace;

    unsigned int vAddr;

    //opens file and checks if file doesnt exist / couldn't open
    FILE *tracef_h = fopen(args.fileName, "r");
    if (!tracef_h) {
        std::cout << "Error: could not open file " << args.fileName<< std::endl;
        return -1;
    }

    // Loop through the entire file.
    while (NextAddress(tracef_h, & mtrace)) {
        vAddr = mtrace.addr;
        table.recordAccess(vAddr);
    }

    // close the file
    fclose(tracef_h);

    return 0;
}