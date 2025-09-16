#pragma once
/* #include <napi.h> */
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
#include "../models/asset.h"


using namespace std;
using json = nlohmann::json;


void from_json(const json &j, Asset &asset)
{
	if (j.contains("name"))
		j.at("name").get_to(asset.name);
	if (j.contains("description"))
		j.at("description").get_to(asset.name);

}