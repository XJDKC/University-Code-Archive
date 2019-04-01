#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>

#include "myFS.h"
using namespace std;

int main() {

    myFS *fs=new myFS();

    fs->init();
    fs->processCommand();
    fs->exit();

    return 0;
}