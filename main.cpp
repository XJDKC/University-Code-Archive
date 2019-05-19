#include <iostream>

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

    MIFParser::exportToMif(mifParser.getVertextHull(),argv[2]);

    return 0;
}