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

typedef struct _RockData
{
    vector<double> Porosity;
    vector<double> PermeabilityX;
    vector<double> PermeabilityY;
    vector<double> PermeabilityZ;
} RockData;