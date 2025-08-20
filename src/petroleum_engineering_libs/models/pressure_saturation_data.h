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

typedef struct _PressureSaturationData
{
    vector<double> pressureOil;
    vector<double> pressureWater;
    vector<double> pressureGas;
    vector<double> saturationOil;
    vector<double> saturationWater;
    vector<double> saturationGas;
} PressureSaturationData;