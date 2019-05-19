//
// Created by xjdkc on 19-5-19.
//

#ifndef MIF_MIF_H
#define MIF_MIF_H

#endif //MIF_MIF_H

#include <string>
#include <list>

struct POINT{
    double x;
    double y;
    std::string symbol;

    POINT();
    POINT(double x, double y);
    POINT(double x, double y,double symbol);
};

struct MIFFile{
    std::string header;
    std::list<POINT> points;

    void clear();
    void addPoint(POINT &point);
};