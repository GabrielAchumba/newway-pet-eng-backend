#pragma once

#include <string>
#include <vector>
#include "src/petroleum_engineering_libs/models/drainage_point_production_data.h"

struct ReservoirProductionData {
    std::string Label;
    std::string Icon;
    std::vector<DrainagePointProductionData> Children;
};