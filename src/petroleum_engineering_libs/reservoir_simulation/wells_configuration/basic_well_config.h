#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include "../../models/pressure_saturation_data.h"
#include "../../models/geometry_data.h"
#include "../../models/rock_data.h"
#include "../initialization/basic_initialization.h"
#include "../utils/grid_indexing.h"
#include "../boundary_conditions/basic_boundary_conditions.h"
#include "../solvers/explicit_finite_difference_solver.h"

using namespace std;
using namespace std::placeholders;

class BasicWellConfig
{
private:
    int NX;
    int NY;
    int NZ;
    GridIndexing gridIndexing;

public:
    BasicWellConfig(int nx, int ny, int nz);

    ~BasicWellConfig();

};

BasicWellConfig::BasicWellConfig(int nx, int ny, int nz)
    : 
    NX(nx), 
    NY(ny), 
    NZ(nz),
    gridIndexing(NX, NY, NZ)
{

}

BasicWellConfig::~BasicWellConfig() = default;

// void ApplyWells(PressureSaturationData& pressureSaturationData) {
//     // Injector: top-left corner at top layer
//     pressureWater[index(NZ - 1, 0, 0)] = 25e6;
//     saturationWater[index(NZ - 1, 0, 0)] = 1.0;
//     saturationOil[index(NZ - 1, 0, 0)] = 0.0;
//     saturationGas[index(NZ - 1, 0, 0)] = 0.0;

//     // Producer: bottom-right corner at bottom layer
//     pressureOil[index(0, NY - 1, NX - 1)] = 15e6;
//     saturationOil[index(0, NY - 1, NX - 1)] = 0.0;
//     saturationWater[index(0, NY - 1, NX - 1)] = 0.0;
//     saturationGas[index(0, NY - 1, NX - 1)] = 1.0;
// }