#pragma once

#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <functional>
#include <exception>
#include <sys/stat.h>
#include <errno.h>
#include <tuple>
#include "../../nlohmann/json.hpp"
#include "../../models/subsurface_assets_payload.h"
#include "../../json_mapping/napi_to_json.h"


using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class ConfigureSubsurfaceAssets
{
private:
    json configuredSubSurfaceAssets;

public:
    ConfigureSubsurfaceAssets();
    ~ConfigureSubsurfaceAssets();
    json Configure(const json &jsonData);
};

ConfigureSubsurfaceAssets::ConfigureSubsurfaceAssets()
{
}

ConfigureSubsurfaceAssets::~ConfigureSubsurfaceAssets()
{
}


json ConfigureSubsurfaceAssets::Configure(const json &jsonData)
{
    SubsurfaceAssetsPayload payload = ConvertJsonToPayload(jsonData);

    return jsonData;
}