//
// Created by xjdkc on 19-5-19.
//

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


void MIFFile::clear() {
    this->header = "";
    this->points.clear();
}

void MIFFile::addPoint(POINT &point) {
    this->points.push_back(point);
}
