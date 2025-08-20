#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include "../utils/grid_indexing.h"

using namespace std;
using namespace std::placeholders;

class BasicBoundaryConditions
{
private:
    int NX;
    int NY;
    int NZ;
    GridIndexing gridIndexing;

public:
    BasicBoundaryConditions(int nx, int ny, int nz);
    ~BasicBoundaryConditions();
    vector<double> ApplyConstantBottomBoundaryConditions(double constantPressure);
    vector<double> ApplyConstantWestBoundaryConditions(double constantPressure);
    vector<double> ApplyConstantEastBoundaryConditions(double constantPressure);
    vector<double> ApplyConstantSouthBoundaryConditions(double constantPressure);
    vector<double> ApplyConstantNorthBoundaryConditions(double constantPressure);

};

BasicBoundaryConditions::BasicBoundaryConditions(int nx, int ny, int nz)
    : NX(nx), NY(ny), NZ(nz), gridIndexing(nx, ny, nz)
{

}

BasicBoundaryConditions::~BasicBoundaryConditions() = default;

vector<double> BasicBoundaryConditions::ApplyConstantBottomBoundaryConditions(double constantPressure) {
    vector<double> pressureWater(NX * NY * NZ, 0);
    for (int j = 0; j < NY; ++j)
        for (int i = 0; i < NX; ++i)
            pressureWater[gridIndexing.index(0, j, i)] = constantPressure; // Bottom layer
}

vector<double> BasicBoundaryConditions::ApplyConstantWestBoundaryConditions(double constantPressure) {
    vector<double> pressureWater(NX * NY * NZ, 0);
    for (int k = 0; k < NZ; ++k)
        for (int j = 0; j < NY; ++j)
            pressureWater[gridIndexing.index(k, j, 0)] = constantPressure; // West layer
}

vector<double> BasicBoundaryConditions::ApplyConstantEastBoundaryConditions(double constantPressure) {
    vector<double> pressureWater(NX * NY * NZ, 0);
    for (int k = 0; k < NZ; ++k)
        for (int j = 0; j < NY; ++j)
            pressureWater[gridIndexing.index(k, j, NX - 1)] = constantPressure; // East layer
}

vector<double> BasicBoundaryConditions::ApplyConstantSouthBoundaryConditions(double constantPressure) {
    vector<double> pressureWater(NX * NY * NZ, 0);
    for (int k = 0; k < NZ; ++k)
        for (int i = 0; i < NX; ++i)
            pressureWater[gridIndexing.index(k, 0, i)] = constantPressure; // South layer
}

vector<double> BasicBoundaryConditions::ApplyConstantNorthBoundaryConditions(double constantPressure) {
    vector<double> pressureWater(NX * NY * NZ, 0);
    for (int k = 0; k < NZ; ++k)
        for (int i = 0; i < NX; ++i)
            pressureWater[gridIndexing.index(k, NY-1, i)] = constantPressure; // North layer
}