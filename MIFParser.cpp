//
// Created by xjdkc on 19-5-19.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>

#include "MIFParser.h"



MIFParser::MIFParser() {

}

MIFParser::MIFParser(const MIFFile mifFile) {
    this->mifFile = mifFile;
}

MIFParser::MIFParser(const std::string filepath) {
    this->filepath = filepath;
}

std::string MIFParser::getFilepath() {
    return this->filepath;
}

void MIFParser::setFilepath(const std::string filename) {
    this->filepath = filename;
}

const MIFFile &MIFParser::getMifFile() const {
    return mifFile;
}

void MIFParser::setMifFile(const MIFFile &mifFile) {
    this->mifFile = mifFile;
}

void MIFParser::parse() {
    std::string line,temp;
    std::ifstream inFile(this->filepath);

    if (!inFile.is_open()){
        std::cout<<"Fail to open the MIF file!"<<std::endl;
        return ;
    }

    this->mifFile.clear();

    while (getline(inFile,line)) {
        temp = line;
        std::transform(temp.begin(),temp.end(),temp.begin(),::toupper);
        if (temp.find("DATA") == 0)
            break;
        this->mifFile.header += line;
    }

    double x,y;
    POINT *point;
    std::string type;
    std::string symbol;

    while (getline(inFile,line)) {
        std::stringstream ss(line);
        ss>>type;
        std::transform(type.begin(),type.end(),type.begin(),::toupper);
        if (type == "POINT") {
            ss >> x >> y;
            point = new POINT(x,y);
            this->mifFile.addPoint(*point);
        }
        else if (type == "SYMBOL"){
            ss >> temp;
            symbol = type + " " + temp;
            this->mifFile.points.back().symbol = symbol;
        }
    }
}

MIFFile MIFParser::getVertextHull() {
    return this->mifFile;
}

void MIFParser::exportToMif(const MIFFile mifFile, const std::string filepath) {
    std::ofstream outFile(filepath);

    if (!outFile.is_open()){
        std::cout<<"Fail to create the output MIF file!"<<std::endl;
        return ;
    }

    outFile<<mifFile.header<<"DATA"<<std::endl;

    for (auto it = mifFile.points.begin();it != mifFile.points.end();++it){
        outFile<<"POINT "<<it->x<<" "<<it->y<<std::endl;
        if (!it->symbol.empty())
            outFile<<"    "<<it->symbol<<std::endl;
    }

}
