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

typedef struct _GeometryData
{
    vector<double> DX;
    vector<double> DY;
    vector<double> DZ;
} GeometryData;