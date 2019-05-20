//
// Created by xjdkc on 19-5-19.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>
#include <iomanip>
#include <cmath>

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
        this->mifFile.header += line + '\n';
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

    inFile.close();
}

MIFFile *MIFParser::getVertextHull() {
    MIFFile *origin = new MIFFile(this->mifFile);

    if (origin->points.size() <= 3)
        return origin;

    int index = 0;

    for (int i = 1; i < origin->points.size() ; i++) {
        if (origin->points[i].y < origin->points[index].y)
            index = i;
    }

    for (int i = 0; i < origin->points.size(); ++i) {
        origin->points[i].x -= this->mifFile.points[index].x;
        origin->points[i].y -= this->mifFile.points[index].y;
        if (origin->points[i].y<0){
            std::cout<<"Error"<<std::endl;
        }
    }

    std::swap(origin->points[0],origin->points[index]);

    std::sort(origin->points.begin(),origin->points.end());

    for (int i = 1; i < origin->points.size(); ++i){
        if (origin->points[i].x == origin->points[i-1].x && origin->points[i].y == origin->points[i-1].y) {
            origin->points.erase(origin->points.begin()+i);
            i = i - 1;
        }
    }

    MIFFile *rtn = new MIFFile();
    rtn->header = this->mifFile.header;
    rtn->points.push_back(origin->points[0]);
    rtn->points.push_back(origin->points[1]);

    for (int i = 2 ; i < origin->points.size(); ++i){
        while (rtn->points.size() >= 2) {
            int top = rtn->points.size()-1;
            double temp = (rtn->points[top].x-rtn->points[top-1].x)*(origin->points[i].y-rtn->points[top-1].y)
                         -(rtn->points[top].y-rtn->points[top-1].y)*(origin->points[i].x-rtn->points[top-1].x);
            if (temp < 0)
                rtn->points.pop_back();
            else
                break;
        }
        rtn->points.push_back(origin->points[i]);
    }

    for (int i = 0; i < rtn->points.size(); ++i) {
        rtn->points[i].x += this->mifFile.points[index].x;
        rtn->points[i].y += this->mifFile.points[index].y;
    }

    delete origin;
    return rtn;

}

void MIFParser::exportToMif(const MIFFile &mifFile, std::string filepath) {
    std::ofstream outFile(filepath);

    if (!outFile.is_open()){
        std::cout<<"Fail to create the output MIF file!"<<std::endl;
        return ;
    }

    outFile<<mifFile.header<<"DATA"<<"\r\n";

    for (auto it = mifFile.points.begin();it != mifFile.points.end();++it){
        outFile<<"POINT "<<it->x<<" "<<it->y<<"\n";
        if (!it->symbol.empty())
            outFile<<"    "<<it->symbol<<"\n";
    }

    outFile.close();
}

void MIFParser::exportToDat(const MIFFile &datFile, std::string filepath) {
    int pos = filepath.find_last_of('.');
    filepath = filepath.substr(0,pos) + ".dat";
    std::ofstream outFile(filepath);

    if (!outFile.is_open()){
        std::cout<<"Fail to create the output DAT file!"<<std::endl;
        return ;
    }

    for (auto it = datFile.points.begin();it != datFile.points.end();++it){
        outFile<<it->x<<" "<<it->y<<"\n";
    }

    outFile.close();
}
