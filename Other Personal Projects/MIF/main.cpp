#include <iostream>

#include <cmath>
#include "MIFParser.h"

using namespace std;

int main(int argc,char **argv) {

    if (argc <= 2) {
        cout<<"Please input command line parameters"<<endl;
        cout<<"MIF <input mif filepath> <output mif filepath>"<<endl;
        return -1;
    }

    MIFParser mifParser(argv[1]);

    mifParser.parse();

    MIFFile *mifFile = mifParser.getVertextHull();

    MIFParser::exportToMif(*mifFile,argv[2]);

    MIFParser::exportToDat(*mifFile,argv[2]);

    return 0;
}