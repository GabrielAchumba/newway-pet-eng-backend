#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <functional>
#include <map>

using namespace std;

typedef struct _FluidData
{
    vector<double> ViscosityOil;
    vector<double> ViscosityWater;
    vector<double> ViscosityGas;
    vector<double> FVFOil;
    vector<double> FVFWater;
    vector<double> FVFGas;
} FluidData;