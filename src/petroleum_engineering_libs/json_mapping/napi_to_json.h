#pragma once

#include "../nlohmann/json.hpp"
#include "subsurface_assets_payload.h"

using namespace std;
using json = nlohmann::json;


SubsurfaceAssetsPayload ConvertJsonToPayload(json jsonData)
{
    SubsurfaceAssetsPayload payload = jsonData.at("payload").get<SubsurfaceAssetsPayload>();
    return payload;
}
