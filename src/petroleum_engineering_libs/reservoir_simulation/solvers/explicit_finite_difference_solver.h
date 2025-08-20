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
#include "../../models/well_data.h"
#include "../utils/grid_indexing.h"

using namespace std;
using namespace std::placeholders;

class ExplicitFiniteDifferenceSolver
{
private:
    int NX;
    int NY;
    int NZ;

    GridIndexing gridIndexing;

    double ComputeDivergence(
        const vector<double>& pressure, 
        double mu,  
        double kx, 
        double ky, 
        double kz, 
        double dx,
        double dy,
        double dz,
        int k, int j, int i
    );

public:
    ExplicitFiniteDifferenceSolver(
        int nx, 
        int ny, 
        int nz);

    ~ExplicitFiniteDifferenceSolver();

    void UpdatePressuresAndSaturations(
        PressureSaturationData& pressureSaturation, 
        double timeStep, 
        FluidData& fluidData,
        GeometryData geometryData, RockData rockData,
        vector<WellData> wells
    );

};

ExplicitFiniteDifferenceSolver::ExplicitFiniteDifferenceSolver(int nx, int ny, int nz)
    : NX(nx), NY(ny), NZ(nz), gridIndexing(NX, NY, NZ)
{

}

ExplicitFiniteDifferenceSolver::~ExplicitFiniteDifferenceSolver() = default;


double ExplicitFiniteDifferenceSolver::ComputeDivergence(
    const vector<double>& pressure, 
    double mu,  
    double kx, 
    double ky, 
    double kz, 
    double dx,
    double dy,
    double dz,
    int k, int j, int i
) {
    int centerIndex = gridIndexing.index(k, j, i);

    int iMinus = gridIndexing.index(k, j, i - 1);
    int iPlus  = gridIndexing.index(k, j, i + 1);

    int jMinus = gridIndexing.index(k, j - 1, i);
    int jPlus  = gridIndexing.index(k, j + 1, i);

    int kMinus = gridIndexing.index(k - 1, j, i);
    int kPlus  = gridIndexing.index(k + 1, j, i);

    double dPx = (pressure[iPlus] - 2 * pressure[centerIndex] + pressure[iMinus]) / (dx * dx);
    double dPy = (pressure[jPlus] - 2 * pressure[centerIndex] + pressure[jMinus]) / (dy * dy);
    double dPz = (pressure[kPlus] - 2 * pressure[centerIndex] + pressure[kMinus]) / (dz * dz);

    return (kx * dPx + ky * dPy + kz * dPz) / mu;
}


void ExplicitFiniteDifferenceSolver::UpdatePressuresAndSaturations(
    PressureSaturationData& pressureSaturation, double timeStep, FluidData& fluidData,
    GeometryData geometryData, RockData rockData, vector<WellData> wells) {

        int nWells = wells.size();

    for (int k = 1; k < NZ - 1; ++k)
        for (int j = 1; j < NY - 1; ++j)
            for (int i = 1; i < NX - 1; ++i) {
                int idx = gridIndexing.index(k, j, i);

                double divOil = ComputeDivergence(pressureSaturation.pressureOil, 
                    fluidData.ViscosityOil[idx],
                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],rockData.PermeabilityZ[idx],
                    geometryData.DX[idx], geometryData.DY[idx], geometryData.DZ[idx],
                    k, j, i);

                double divWater = ComputeDivergence(pressureSaturation.pressureWater, 
                    fluidData.ViscosityWater[idx], 
                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],rockData.PermeabilityZ[idx],
                    geometryData.DX[idx], geometryData.DY[idx], geometryData.DZ[idx], 
                    k, j, i);

                double divGas = ComputeDivergence(pressureSaturation.pressureGas, 
                    fluidData.ViscosityGas[idx], 
                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],rockData.PermeabilityZ[idx],
                    geometryData.DX[idx], geometryData.DY[idx], geometryData.DZ[idx], 
                    k, j, i);

                for(int wellIndex = 0; wellIndex < nWells; wellIndex++){

                    int nPerforations =  wells[wellIndex].perforationPositions.size();

                    for(int perforationIndex = 0; perforationIndex < nPerforations; perforationIndex++){

                        if(wells[wellIndex].isPeforated(
                            wells[wellIndex].perforationPositions[perforationIndex].i,
                            wells[wellIndex].perforationPositions[perforationIndex].j,
                            wells[wellIndex].perforationPositions[perforationIndex].k,
                            i, j, k)){

                         
                                if(wells[wellIndex].wellType == 1){ // Oil Producer Well

                                    divOil -= wells[wellIndex].calculateFlowRate(
                                    geometryData.DX[idx], geometryData.DY[idx], 
                                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],
                                    geometryData.DZ[idx], fluidData.ViscosityOil[idx],
                                    fluidData.FVFOil[idx], pressureSaturation.pressureOil[idx]);
                                }

                         
                                if(wells[wellIndex].wellType == 2){ // Gas Producer Well

                                    divOil -= wells[wellIndex].calculateFlowRate(
                                    geometryData.DX[idx], geometryData.DY[idx], 
                                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],
                                    geometryData.DZ[idx], fluidData.ViscosityGas[idx],
                                    fluidData.FVFGas[idx], pressureSaturation.pressureGas[idx]);
                                }

                         
                                if(wells[wellIndex].wellType == 3){ // Water Injector Well

                                    divWater += wells[wellIndex].calculateFlowRate(
                                    geometryData.DX[idx], geometryData.DY[idx], 
                                    rockData.PermeabilityX[idx],rockData.PermeabilityY[idx],
                                    geometryData.DZ[idx], fluidData.ViscosityWater[idx],
                                    fluidData.FVFWater[idx], pressureSaturation.pressureWater[idx]);
                                }

                        }
                    }
                    
                    
                }


                pressureSaturation.pressureOil[idx] += timeStep * divOil / rockData.Porosity[idx];
                pressureSaturation.pressureWater[idx] += timeStep * divWater / rockData.Porosity[idx];
                pressureSaturation.pressureGas[idx] += timeStep * divGas / rockData.Porosity[idx];

                // Instead of using 0.001 use tuner = (DT / (porosity * DX * DY * DZ))

                double tuner = (
                    timeStep / 
                    (rockData.Porosity[idx] * geometryData.DX[idx] * geometryData.DY[idx] * geometryData.DZ[idx])
                );

                double so = pressureSaturation.saturationOil[idx] + tuner * divOil;
                double sw = pressureSaturation.saturationWater[idx] + tuner * divWater;
                double sg = pressureSaturation.saturationGas[idx] + tuner * divGas;

                double total = max(so + sw + sg, 1e-6);
                pressureSaturation.saturationOil[idx] = so / total;
                pressureSaturation.saturationWater[idx] = sw / total;
                pressureSaturation.saturationGas[idx] = sg / total;
            }
}