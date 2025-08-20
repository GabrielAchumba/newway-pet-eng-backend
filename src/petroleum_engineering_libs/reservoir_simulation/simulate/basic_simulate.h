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

class BasicSimulate
{
private:
    int NX;
    int NY;
    int NZ;
    double porosity;
    double permeabilityX;
    double permeabilityY;
    double permeabilityZ;
    double dx;
    double dy;
    double dz;
    double oilViscosity;
    double waterViscosity;
    double gasViscosity;
    double oilFVF; 
    double waterFVF; 
    double gasFVF;
    double pressureOil;
    double pressureWater;
    double pressureGas;
    double saturationOil;
    double saturationWater;
    double saturationGas;
    GridIndexing gridIndexing;
    BasicInitialization basicInitialization;
    BasicBoundaryConditions basicBoundaryConditions;
    ExplicitFiniteDifferenceSolver explicitFiniteDifferenceSolver;
    void PrintMidpointState(
    int timeStep, 
    PressureSaturationData& pressureSaturationData);

public:
    BasicSimulate(int nx, int ny, int nz, double _porosity, 
    double _permeabilityX, double _permeabilityY, double _permeabilityZ, 
    double _dx, double _dy, double _dz,
    double _oilViscosity, double _waterViscosity, double _gasViscosity,
    double _oilFVF, double _waterFVF, double _gasFVF,
    double _pressureOil, double _pressureWater, double _pressureGas, 
    double _saturationOil, double _saturationWater, double _saturationGas);
    ~BasicSimulate();

    void Simulate(
    int MAX_TIME_STEPS,
    double timeStep,
    vector<WellData> wells,
    double bottomBoundaryPressure = 0,
    double westBoundaryPressure = 0,
    double eastBoundaryPressure = 0,
    double southBoundaryPressure = 0,
    double northBoundaryPressure = 0);

};

BasicSimulate::BasicSimulate(int nx, int ny, int nz, double _porosity,
    double _permeabilityX, double _permeabilityY, double _permeabilityZ, 
    double _dx, double _dy, double _dz,
    double _oilViscosity, double _waterViscosity, double _gasViscosity,
    double _oilFVF, double _waterFVF, double _gasFVF,
    double _pressureOil, double _pressureWater, double _pressureGas, 
    double _saturationOil, double _saturationWater, double _saturationGas)
    : 
    NX(nx), 
    NY(ny), 
    NZ(nz), 
    porosity(_porosity), 
    permeabilityX(_permeabilityX), 
    permeabilityY(_permeabilityY), 
    permeabilityZ(_permeabilityZ), 
    dx(_dx), 
    dy(_dy), 
    dz(_dz),  
    oilViscosity(_oilViscosity),  
    waterViscosity(_waterViscosity),  
    gasViscosity(_gasViscosity), 
    oilFVF(_oilFVF),  
    waterFVF(_waterFVF),  
    gasFVF(_gasFVF),   
    pressureOil(_pressureOil),   
    pressureWater(_pressureWater),   
    pressureGas(_pressureGas),   
    saturationOil(_saturationOil),   
    saturationWater(_saturationWater),   
    saturationGas(_saturationGas), 
    gridIndexing(NX, NY, NZ),
    basicInitialization(NX, NY, NZ),
    basicBoundaryConditions(NX, NY, NZ),
    explicitFiniteDifferenceSolver(NX, NY, NZ)
{

}

BasicSimulate::~BasicSimulate() = default;

void BasicSimulate::PrintMidpointState(
    int timeStep, 
    PressureSaturationData& pressureSaturationData) {
    int i = NX / 2, j = NY / 2, k = NZ / 2;
    int idx = gridIndexing.index(k, j, i);
    cout << fixed << setprecision(2);
    cout << "Step " << timeStep
         << " | Po: " << pressureSaturationData.pressureOil[idx] / 1e6 << " MPa"
         << " | So: " << pressureSaturationData.saturationOil[idx] << endl;
}

void BasicSimulate::Simulate(
    int MAX_TIME_STEPS,
    double timeStep,
    vector<WellData> wells,
    double bottomBoundaryPressure = 0,
    double westBoundaryPressure = 0,
    double eastBoundaryPressure = 0,
    double southBoundaryPressure = 0,
    double northBoundaryPressure = 0
    ) {

    RockData rockData = basicInitialization.InitializeRockData(porosity, permeabilityX, permeabilityY, permeabilityZ);

    GeometryData geometryData = basicInitialization.InitializeGeometryData(dx, dy, dz);

    FluidData fluidData = basicInitialization.InitializeFluidData(oilViscosity, waterViscosity, gasViscosity,
    oilFVF, waterFVF, gasFVF);

    PressureSaturationData pressureSaturationData = 
    basicInitialization.InitializePressureSaturation(pressureOil, pressureWater, pressureGas, 
        saturationOil, saturationWater, saturationGas);

    for (int t = 0; t < MAX_TIME_STEPS; ++t) {
        basicBoundaryConditions.ApplyConstantBottomBoundaryConditions(bottomBoundaryPressure);
        basicBoundaryConditions.ApplyConstantEastBoundaryConditions(westBoundaryPressure);
        basicBoundaryConditions.ApplyConstantWestBoundaryConditions(eastBoundaryPressure);
        basicBoundaryConditions.ApplyConstantSouthBoundaryConditions(southBoundaryPressure);
        basicBoundaryConditions.ApplyConstantNorthBoundaryConditions(northBoundaryPressure);

        explicitFiniteDifferenceSolver.UpdatePressuresAndSaturations(pressureSaturationData, 
            timeStep, fluidData, geometryData, rockData, wells);

        if (t % 10 == 0)
            PrintMidpointState(t, pressureSaturationData);
    }

}