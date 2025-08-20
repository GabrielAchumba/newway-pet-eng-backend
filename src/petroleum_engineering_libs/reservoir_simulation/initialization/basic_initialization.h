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
#include "../../models/fluid_data.h"
#include "../utils/grid_indexing.h"

using namespace std;
using namespace std::placeholders;

class BasicInitialization
{
private:
    int NX;
    int NY;
    int NZ;
    GridIndexing gridIndexing;

public:
    BasicInitialization(int nx, int ny, int nz);
    ~BasicInitialization();

    PressureSaturationData InitializePressureSaturation(
    double pressureOil,
    double pressureWater,
    double pressureGas,
    double saturationOil,
    double saturationWater,
    double saturationGas);

    GeometryData InitializeGeometryData(
    double dx,
    double dy,
    double dz);

    RockData InitializeRockData(
    double porosity,
    double permeabilityX,
    double permeabilityY,
    double permeabilityZ);

    FluidData InitializeFluidData(
    double oilViscosity,
    double waterViscosity,
    double gasViscosity,
    double oilFVF,
    double waterFVF,
    double gasFVF);

};

BasicInitialization::BasicInitialization(int nx, int ny, int nz)
    : NX(nx), NY(ny), NZ(nz), gridIndexing(NX, NY, NZ)
{

}

BasicInitialization::~BasicInitialization() = default;

PressureSaturationData BasicInitialization::InitializePressureSaturation(
    double pressureOil,
    double pressureWater,
    double pressureGas,
    double saturationOil,
    double saturationWater,
    double saturationGas) {

    PressureSaturationData pressureSaturation;

    int totalCells = NX * NY * NZ;

    pressureSaturation.pressureOil.assign(totalCells, pressureOil);
    pressureSaturation.pressureWater.assign(totalCells, pressureWater);
    pressureSaturation.pressureGas.assign(totalCells, pressureGas);

    pressureSaturation.saturationOil.assign(totalCells, saturationOil);
    pressureSaturation.saturationWater.assign(totalCells, saturationWater);
    pressureSaturation.saturationGas.assign(totalCells, saturationGas);

    pressureSaturation.saturationOil.assign(totalCells, saturationOil);
    pressureSaturation.saturationWater.assign(totalCells, saturationWater);
    pressureSaturation.saturationGas.assign(totalCells, saturationGas);

    pressureSaturation.saturationOil.assign(totalCells, saturationOil);
    pressureSaturation.saturationWater.assign(totalCells, saturationWater);

    return pressureSaturation;

}

GeometryData BasicInitialization::InitializeGeometryData(
    double dx,
    double dy,
    double dz) {

    GeometryData geometryData;

    int totalCells = NX * NY * NZ;

    geometryData.DX.assign(totalCells, dx);
    geometryData.DY.assign(totalCells, dy);
    geometryData.DZ.assign(totalCells, dz);

    return geometryData;

}

RockData BasicInitialization::InitializeRockData(
    double porosity,
    double permeabilityX,
    double permeabilityY,
    double permeabilityZ) {

    RockData rockData;

    int totalCells = NX * NY * NZ;

    rockData.Porosity.assign(totalCells, porosity);
    rockData.PermeabilityX.assign(totalCells, permeabilityX);
    rockData.PermeabilityY.assign(totalCells, permeabilityY);
    rockData.PermeabilityZ.assign(totalCells, permeabilityZ);

    return rockData;

}

FluidData BasicInitialization::InitializeFluidData(
    double oilViscosity,
    double waterViscosity,
    double gasViscosity,
    double oilFVF,
    double waterFVF,
    double gasFVF) {

    FluidData fluidData;

    int totalCells = NX * NY * NZ;

    fluidData.ViscosityGas.assign(totalCells, gasViscosity);
    fluidData.ViscosityOil.assign(totalCells, oilViscosity);
    fluidData.ViscosityWater.assign(totalCells, waterViscosity);

    fluidData.FVFGas.assign(totalCells, gasFVF);
    fluidData.FVFOil.assign(totalCells, oilFVF);
    fluidData.FVFWater.assign(totalCells, waterFVF);

    return fluidData;

}
