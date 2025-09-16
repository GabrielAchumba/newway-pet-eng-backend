#pragma once

#include <vector>
#include "./asset.h"

typedef struct _SubsurfaceAssetsPayload
{
    vector<Asset> wells;
    vector<Asset> reservoirs;
    vector<Asset> fields;
    vector<Asset> productionStrings;
    vector<Asset> wellProductionStrings;
} SubsurfaceAssetsPayload;