#pragma once

// #include "node_modules/node-addon-api/napi.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <tuple>
#include "../nlohmann/json.hpp"
#include "../models/subsurface_assets_payload.h"
#include "./asset_json.h"

using namespace std;
using json = nlohmann::json;

void from_json(const json &j, SubsurfaceAssetsPayload &payload)
{
    for (const auto &item : j.at("wells"))
    {
        Asset asset;
        from_json(item, asset);
        payload.wells.push_back(asset);
    }

    for (const auto &item : j.at("reservoirs"))
    {
        Asset asset;
        from_json(item, asset);
        payload.reservoirs.push_back(asset);
    }

    for (const auto &item : j.at("fields"))
    {
        Asset asset;
        from_json(item, asset);
        payload.fields.push_back(asset);
    }

    for (const auto &item : j.at("productionStrings"))
    {
        Asset asset;
        from_json(item, asset);
        payload.productionStrings.push_back(asset);
    }
    
    for (const auto &item : j.at("wellProductionStrings"))
    {
        Asset asset;
        from_json(item, asset);
        payload.wellProductionStrings.push_back(asset);
    }
}