#pragma once

#include <string>
#include <vector>
#include "src/petroleum_engineering_libs/models/date.h"

typedef struct _ProductionDataCollection {
    std::vector<Date> ProductionDates;
    std::vector<double> CumulativeProductionDays;
    std::vector<double> CumulativeOilProduced;
    std::vector<double> CumulativeGasProduced;
    std::vector<double> CumulativeWaterProduced;
    std::vector<double> CumulativeWaterInjected;
    std::vector<double> CumulativeGasInjected;
    std::vector<double> CumulativeLiquidProduced;
}ProductionDataCollection;





