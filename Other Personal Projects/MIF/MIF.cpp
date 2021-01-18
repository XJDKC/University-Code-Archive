//
// Created by xjdkc on 19-5-19.
//

#include <cmath>

#include "MIF.h"

POINT::POINT() {

}

POINT::POINT(double x, double y) {
    this->x = x;
    this->y = y;
}

POINT::POINT(double x, double y, double symbol) {
    this->x = x;
    this->y = y;
    this->symbol = symbol;
}

bool POINT::operator<(const POINT &a) const {
    if(atan2(a.y,a.x)!=atan2(this->y,this->x))
        return atan2(this->y,this->x)<atan2(a.y,a.x);
    return this->x<a.x;
}

MIFFile::MIFFile() {

}

MIFFile::MIFFile(MIFFile &mifFile) {
    this->header = mifFile.header;
    this->points = mifFile.points;
}


void MIFFile::clear() {
    this->header = "";
    this->points.clear();
}

void MIFFile::addPoint(POINT &point) {
    this->points.push_back(point);
}


