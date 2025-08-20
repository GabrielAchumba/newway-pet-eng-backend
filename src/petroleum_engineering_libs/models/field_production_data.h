#pragma once

#include <string>
#include <vector>
#include "src/petroleum_engineering_libs/models/reservoir_production_data.h"

struct FieldProductionData {
    std::string Label;
    std::string Icon;
    std::vector<ReservoirProductionData> Children;
};