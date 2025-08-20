#pragma once

#include <string>
#include <vector>
#include "src/petroleum_engineering_libs/models/date.h"

typedef struct _ProductionData {
    std::string Lease;
    std::string FacilityName;
    std::string Field;
    std::string Reservoir;
    std::string TubingString;
    std::string DrainagePoint;
    std::string Date1;
    Date Date2;

    int Day;
    int Month;
    int Year;

    double SplitFactor;
    double MonthlyOilProduced;
    double MonthlyGasProduced;
    double MonthlyWaterProduced;
    double MonthlyGasInjected;
    double MonthlyWaterInjected;
    double MonthlyLiquidProduced;
    double LiquidProduced;

    double MonthlyOilProdDaysRate;
    double MonthlyGasProdDaysRate;
    double MonthlyWaterProdDaysRate;
    double MonthlyLiquidProdDaysRate;
    double MonthlyGasInjectionProdDaysRate;
    double MonthlyWaterInjectionProdDaysRate;

    double MonthlyOilCalendarDaysRate;
    double MonthlyGasCalendarDaysRate;
    double MonthlyWaterCalendarDaysRate;
    double MonthlyLiquidCalendarDaysRate;
    double MonthlyGasInjectionCalendarDaysRate;
    double MonthlyWaterInjectionCalendarDaysRate;

    double ProdHours;
    double ProdDays;
    double DefermentFactor;
    double CumulativeOilProduced;
    double CumulativeGasProduced;
    double CumulativeWaterProduced;
    double CumulativeWaterInjected;
    double CumulativeGasInjected;
    double CumulativeLiquidProduced;
    double UltimateRecovery;

    double WaterCut;
    double ProdGOR;
    double WaterGasRatio;
    double CondensateGasRatio;
    double MonthlyProdTHP;
    double MonthlyProdBean;
    double MonthlyProdSand;
    double ReservoirPressure;
}ProductionData;