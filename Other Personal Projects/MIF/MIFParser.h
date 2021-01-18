//
// Created by xjdkc on 19-5-19.
//

#ifndef MIF_MIFPARSER_H
#define MIF_MIFPARSER_H

#include <string>

#include "MIF.h"

class MIFParser{

private:
    std::string filepath;
    MIFFile mifFile;

public:
    MIFParser();
    MIFParser(const MIFFile mifFile);
    MIFParser(const std::string filepath);

    std::string getFilepath();
    void setFilepath(const std::string filename);
    const MIFFile &getMifFile() const;
    void setMifFile(const MIFFile &mifFile);

    void parse();
    MIFFile *getVertextHull();
    static void exportToMif(const MIFFile &mifFile, std::string filepath);
    static void exportToDat(const MIFFile &datFile, std::string filepath);

};

#endif //MIF_MIFPARSER_H
