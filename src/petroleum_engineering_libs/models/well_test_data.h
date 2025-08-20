#pragma once

#include <string>
#include <vector>
#include "src/petroleum_engineering_libs/models/date.h"

typedef struct _WellTestData {
    std::string Lease;
    std::string FacilityName;
    std::string Field;
    std::string Reservoir;
    std::string TubingString;
    std::string DrainagePoint;
    std::string Facility;

    Date Date1; 
    std::string Date2;

    int Day;
    int Month;
    int Year;

    double ChokeSize;
    double THPNew;
    double WellHeadTemperature;
    double FlowLineTemperature;
    double FlowLinePressure;
    double ManifoldPressure;
    double SeparatorPressure;
    double SeparatorTemperature;
    double CasingHeadPressure;

    double LiquidNew;
    double GasNew;
    double OilNew;
    double WaterNew;
    double WaterCut;
    double ProdGOR;
    double CondensateGasRatio;
    double WaterGasRatio;
    double DailyLiquidVolume;
    double ProdDays;
}WellTestData;