//
// Created by xjdkc on 19-5-19.
//

#ifndef MIF_MIF_H
#define MIF_MIF_H

#endif //MIF_MIF_H

#include <string>
#include <vector>

struct POINT{
    double x;
    double y;
    std::string symbol;

    POINT();
    POINT(double x, double y);
    POINT(double x, double y,double symbol);

    bool operator<(const POINT &a) const;
};

struct MIFFile{
    std::string header;
    std::vector<POINT> points;

    MIFFile();
    MIFFile(MIFFile &mifFile);

    void clear();
    void addPoint(POINT &point);
};