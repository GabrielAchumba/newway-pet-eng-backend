#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>

using namespace std;
using namespace std::placeholders;

class GridIndexing
{
private:
    int NX;
    int NY;
    int NZ;

public:
    GridIndexing(int nx, int ny, int nz);
    ~GridIndexing();
    inline int index(int k, int j, int i);

};

GridIndexing::GridIndexing(int nx, int ny, int nz)
    : NX(nx), NY(ny), NZ(nz)
{

}

GridIndexing::~GridIndexing() = default;


// 3D field represented as 1D vector
inline int GridIndexing::index(int k, int j, int i) {
    return k * NY * NX + j * NX + i;
}