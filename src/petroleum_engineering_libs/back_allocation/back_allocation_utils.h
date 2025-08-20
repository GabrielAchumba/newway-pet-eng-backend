#pragma once

#include <vector>
#include <string>
#include <tuple>
#include "src/petroleum_engineering_libs/models/date.h"
#include "src/petroleum_engineering_libs/models/production_data.h"
#include "src/petroleum_engineering_libs/utils/asset_explorer_generation.h"
#include "src/petroleum_engineering_libs/models/well_test_data.h"
#include "src/petroleum_engineering_libs/back_allocation/back_allocate.h"
#include "src/petroleum_engineering_libs/back_allocation/allocation_methods.h"


// Global variables (not recommended, but matching the Go code)
AllocationMethods allocationMethods;
AssetExplorerGeneration assetExplorerGeneration;
BackAllocate backAllocate;



std::vector<ProductionData> CalculateProductionData1(
    const std::vector<ProductionData>& allProdData,
    const std::string& timeFrequency,
    double trunkLineReconciliationFactor) {
    
    std::vector<Date> dates = assetExplorerGeneration.GetListOfYears1(allProdData, timeFrequency);
    std::vector<ProductionData> results;
    
    if (timeFrequency == "daily") {
        results = backAllocate.GetDailyProductionDataHighNodeLevel(allProdData, dates);
    } else {
        results = backAllocate.GetMonthlyProductionDataHighNodeLevel(
            allProdData, dates, trunkLineReconciliationFactor);
    }
    
    return results;
}

std::tuple<std::vector<std::vector<ProductionData>>,
           std::vector<std::vector<WellTestData>>,
           std::vector<std::vector<ProductionData>>,
           std::vector<double>,
           double>
TestAllocationMethod1(
    const std::vector<ProductionData>& allProdData,
    const std::string& timeFrequency,
    const std::vector<WellTestData>& listOfWellTestData,
    double trunkLineReconciliationFactor) {
    
    std::string allocationMethod = "method1";
    auto [productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError] = 
        allocationMethods.AllocationMethod1(
            allProdData,
            timeFrequency,
            listOfWellTestData,
            trunkLineReconciliationFactor,
            allocationMethod);
    
    return {productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError};
}

std::tuple<std::vector<std::vector<ProductionData>>,
           std::vector<std::vector<WellTestData>>,
           std::vector<std::vector<ProductionData>>,
           std::vector<double>,
           double>
TestAllocationMethod2(
    const std::vector<ProductionData>& allProdData,
    const std::string& timeFrequency,
    const std::vector<WellTestData>& listOfWellTestData,
    double trunkLineReconciliationFactor,
    const std::vector<ProductionData>& facilityDailyProdDataList) {
    
    std::string allocationMethod = "method2";
    auto [productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError] = 
        allocationMethods.AllocationMethod2(
            allProdData,
            timeFrequency,
            listOfWellTestData,
            trunkLineReconciliationFactor,
            allocationMethod,
            facilityDailyProdDataList);
    
    return {productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError};
}