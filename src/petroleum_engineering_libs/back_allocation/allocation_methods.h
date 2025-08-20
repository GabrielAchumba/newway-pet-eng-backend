#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "src/petroleum_engineering_libs/models/date.h"
#include "src/petroleum_engineering_libs/models/production_data.h"
#include "src/petroleum_engineering_libs/models/well_test_data.h"
#include "src/petroleum_engineering_libs/utils/date_creation.h"
#include "src/petroleum_engineering_libs/back_allocation/well_test_data_analysis.h"
#include "src/petroleum_engineering_libs/utils/asset_explorer_generation.h"
#include "src/petroleum_engineering_libs/back_allocation/back_allocate.h"


class AllocationMethods {
private:
    DateCreation dateCreation;
    WellTestDataAnalysis wellTestDataAnalysis;
    AssetExplorerGeneration assetExplorerGeneration;
    BackAllocate backAllocate;

public:
    std::vector<ProductionData> GetDailyProductionDataReadingsDrainagePointLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& dates, 
        const std::string& selectedDrainagePoint,
        int initialIndex) {
        
        std::vector<ProductionData> results;
        size_t lent = dates.size();
        
        for (size_t i = 0; i < lent; i++) {
            ProductionData productionData = listOfProductionData[initialIndex];
            productionData.Day = dates[i].Day;
            productionData.Month = dates[i].Month;
            productionData.Year = dates[i].Year;
            results.push_back(productionData);
        }

        size_t lent2 = listOfProductionData.size();
        for (size_t i = 0; i < lent; i++) {
            double dLp = 0;

            for (size_t j = 0; j < lent2; j++) {
                if (results[i].Year == listOfProductionData[j].Year &&
                    results[i].Month == listOfProductionData[j].Month &&
                    results[i].Day == listOfProductionData[j].Day &&
                    listOfProductionData[j].DrainagePoint == selectedDrainagePoint) {
                    dLp += listOfProductionData[j].LiquidProduced;
                }
            }

            results[i].LiquidProduced = dLp;
        }

        return results;
    }

    std::vector<ProductionData> GetMonthlyProductionDataReadingsDrainagePointLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& dates, 
        const std::string& selectedDrainagePoint,
        int initialIndex, 
        const std::string& allocationMethod) {
        
        std::vector<ProductionData> results;
        size_t lent = dates.size();
        size_t lent2 = listOfProductionData.size();

        for (size_t i = 0; i < lent; i++) {
            ProductionData productionData = listOfProductionData[initialIndex];
            productionData.Day = dates[i].Day;
            productionData.Month = dates[i].Month;
            productionData.Year = dates[i].Year;
            results.push_back(productionData);
        }

        for (size_t i = 0; i < lent; i++) {
            double dLp = 0;
            double prodDays = 0;
            double daysInMonth = static_cast<double>(dateCreation.DaysInMonth(results[i].Month));
            
            for (size_t j = 0; j < lent2; j++) {
                if (listOfProductionData[j].DrainagePoint == selectedDrainagePoint &&
                    results[i].Year == listOfProductionData[j].Year &&
                    results[i].Month == listOfProductionData[j].Month) {
                    dLp += listOfProductionData[j].LiquidProduced;
                    
                    if (allocationMethod == "method1") {
                        if (listOfProductionData[j].LiquidProduced > 0) {
                            prodDays++;
                        }
                    } else {
                        double day = listOfProductionData[j].ProdHours / 24.0;
                        prodDays += day;
                    }
                }
            }

            results[i].LiquidProduced = dLp;
            results[i].ProdDays = prodDays;
            results[i].DefermentFactor = (prodDays - daysInMonth) / daysInMonth;
        }

        return results;
    }

    std::vector<ProductionData> GetYearlyProductionDataReadingsDrainagePointLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& dates, 
        const std::string& selectedDrainagePoint,
        int initialIndex) {
        
        std::vector<ProductionData> results;
        size_t lent = dates.size();
        
        for (size_t i = 0; i < lent; i++) {
            ProductionData productionData = listOfProductionData[initialIndex];
            productionData.Day = dates[i].Day;
            productionData.Month = dates[i].Month;
            productionData.Year = dates[i].Year;
            results.push_back(productionData);
        }

        size_t lent2 = listOfProductionData.size();
        for (size_t i = 0; i < lent; i++) {
            double dLp = 0;
            double prodDays = 0;
            double daysInMonths = 365;
            
            for (size_t j = 0; j < lent2; j++) {
                if (results[i].Year == listOfProductionData[j].Year &&
                    listOfProductionData[j].DrainagePoint == selectedDrainagePoint) {
                    dLp += listOfProductionData[j].LiquidProduced;
                    if (listOfProductionData[j].LiquidProduced > 0) {
                        prodDays++;
                    }
                }
            }

            results[i].LiquidProduced = dLp;
            results[i].ProdDays = prodDays;
            results[i].DefermentFactor = (prodDays - daysInMonths) / daysInMonths;
        }

        return results;
    }

    std::vector<ProductionData> GetReconciledProductionDataDrainagePointLevel(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates,
        const std::vector<ProductionData>& listOfProductionData,
        const std::string& selectedDrainagePoint,
        double trunkLineReconciliationFactor) {
        
        std::vector<ProductionData> results;
        size_t lent = dates.size();
        
        for (size_t i = 0; i < lent; i++) {
            WellTestData wellTestData = wellTestDataAnalysis.GetCurrentWellTestData(listOfWellTestData, dates[i], selectedDrainagePoint);
            ProductionData prodData = wellTestDataAnalysis.GetCurrentProductionData(listOfProductionData, dates[i]);
            prodData.Day = dates[i].Day;
            prodData.Month = dates[i].Month;
            prodData.Year = dates[i].Year;
            prodData.MonthlyLiquidProduced = prodData.LiquidProduced * trunkLineReconciliationFactor;
            prodData.MonthlyOilProduced = (1 - (wellTestData.WaterCut / 100)) * prodData.MonthlyLiquidProduced;
            prodData.MonthlyWaterProduced = (wellTestData.WaterCut / 100) * prodData.MonthlyLiquidProduced;
            prodData.MonthlyGasProduced = prodData.MonthlyOilProduced * wellTestData.ProdGOR;
            results.push_back(prodData);
        }

        return results;
    }

    std::vector<ProductionData> GetReconciledProductionDataDrainagePointLevel2(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates,
        const std::vector<ProductionData>& listOfProductionData,
        const std::string& selectedDrainagePoint,
        const std::vector<ProductionData>& facilityProductionData,
        const std::vector<WellTestData>& facilityWellTestData) {
        
        std::vector<ProductionData> results;
        size_t lent = dates.size();
        
        for (size_t i = 0; i < lent; i++) {
            WellTestData wellTestData = wellTestDataAnalysis.GetCurrentWellTestData(listOfWellTestData, dates[i], selectedDrainagePoint);
            ProductionData prodData = wellTestDataAnalysis.GetCurrentProductionData(listOfProductionData, dates[i]);
            prodData.Day = dates[i].Day;
            prodData.Month = dates[i].Month;
            prodData.Year = dates[i].Year;
            prodData.SplitFactor = 0;
            if (facilityWellTestData[i].LiquidNew > 0) {
                prodData.SplitFactor = wellTestData.LiquidNew / facilityWellTestData[i].LiquidNew;
            }
            prodData.MonthlyLiquidProduced = prodData.SplitFactor * facilityProductionData[i].LiquidProduced;
            prodData.MonthlyOilProduced = (1 - (wellTestData.WaterCut / 100)) * prodData.MonthlyLiquidProduced;
            prodData.MonthlyWaterProduced = (wellTestData.WaterCut / 100) * prodData.MonthlyLiquidProduced;
            prodData.MonthlyGasProduced = prodData.MonthlyOilProduced * wellTestData.ProdGOR;
            results.push_back(prodData);
        }

        return results;
    }

    std::vector<std::vector<ProductionData>> GetProductionDataReadingsDrainagePointsLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& dates, 
        const std::string& timeFrequency,
        const std::vector<std::string>& drainagePointNames,
        const std::string& allocationMethod) {
        
        std::vector<std::vector<ProductionData>> results;
        size_t lent = drainagePointNames.size();
        size_t lent2 = listOfProductionData.size();
        
        for (size_t i = 0; i < lent; i++) {
            int initialIndex = 0;
            for (size_t j = 0; j < lent2; j++) {
                if (drainagePointNames[i] == listOfProductionData[j].DrainagePoint) {
                    initialIndex = j;
                    break;
                }
            }

            if (timeFrequency == "yearly") {
                results.push_back(
                    GetYearlyProductionDataReadingsDrainagePointLevel(listOfProductionData,
                        dates, drainagePointNames[i], initialIndex));
            }
            if (timeFrequency == "monthly") {
                results.push_back(
                    GetMonthlyProductionDataReadingsDrainagePointLevel(listOfProductionData,
                        dates, drainagePointNames[i], initialIndex, allocationMethod));
            }
            if (timeFrequency == "daily") {
                results.push_back(
                    GetDailyProductionDataReadingsDrainagePointLevel(listOfProductionData,
                        dates, drainagePointNames[i], initialIndex));
            }
        }

        return results;
    }

    std::vector<std::vector<ProductionData>> GetReconciledProductionDataDrainagePointsLevel(
        const std::vector<std::vector<ProductionData>>& listOfProductionData,
        const std::vector<std::vector<WellTestData>>& listOfWellTestData,
        const std::vector<Date>& dates, 
        const std::string& timeFrequency,
        double trunkLineReconciliationFactor) {
        
        std::vector<std::vector<ProductionData>> results;
        size_t lent = listOfProductionData.size();
        
        for (size_t i = 0; i < lent; i++) {
            std::string selectedDrainagePoint = listOfProductionData[i][0].DrainagePoint;
            results.push_back(
                GetReconciledProductionDataDrainagePointLevel(listOfWellTestData[i],
                    dates, listOfProductionData[i],
                    selectedDrainagePoint, trunkLineReconciliationFactor));
        }

        return results;
    }

    std::vector<std::vector<ProductionData>> GetReconciledProductionDataDrainagePointsLevel2(
        const std::vector<std::vector<ProductionData>>& listOfProductionData,
        const std::vector<std::vector<WellTestData>>& listOfWellTestData,
        const std::vector<Date>& dates, 
        const std::string& timeFrequency,
        const std::vector<ProductionData>& facilityProductionData,
        const std::vector<WellTestData>& facilityWellTestData) {
        
        std::vector<std::vector<ProductionData>> results;
        size_t lent = listOfProductionData.size();
        
        for (size_t i = 0; i < lent; i++) {
            std::string selectedDrainagePoint = listOfProductionData[i][0].DrainagePoint;
            results.push_back(
                GetReconciledProductionDataDrainagePointLevel2(listOfWellTestData[i],
                    dates, listOfProductionData[i],
                    selectedDrainagePoint, facilityProductionData,
                    facilityWellTestData));
        }

        return results;
    }

    std::vector<ProductionData> GetMonthlyProdDataDataHighNodeLevel(
        const std::vector<std::vector<ProductionData>>& listOfProdData,
        const std::vector<Date>& monthlydates) {
        
        std::vector<ProductionData> results;
        size_t lent = monthlydates.size();
        
        for (size_t i = 0; i < lent; i++) {
            ProductionData prodDataData;
            prodDataData.Day = monthlydates[i].Day;
            prodDataData.Month = monthlydates[i].Month;
            prodDataData.Year = monthlydates[i].Year;

            prodDataData.Lease = listOfProdData[0][0].Lease;
            prodDataData.Field = listOfProdData[0][0].Field;
            prodDataData.FacilityName = listOfProdData[0][0].FacilityName;
            prodDataData.Reservoir = listOfProdData[0][0].Reservoir;
            prodDataData.TubingString = listOfProdData[0][0].TubingString;
            prodDataData.DrainagePoint = listOfProdData[0][0].DrainagePoint;

            results.push_back(prodDataData);
        }

        lent = listOfProdData.size();
        for (size_t i = 0; i < lent; i++) {
            size_t lent2 = listOfProdData[i].size();
            for (size_t j = 0; j < lent2; j++) {
                results[j].MonthlyOilProduced += listOfProdData[i][j].MonthlyOilProduced;
                results[j].MonthlyWaterProduced += listOfProdData[i][j].MonthlyWaterProduced;
                results[j].MonthlyGasProduced += listOfProdData[i][j].MonthlyGasProduced;
                results[j].MonthlyLiquidProduced += listOfProdData[i][j].MonthlyLiquidProduced;
            }
        }

        return results;
    }

    std::pair<std::vector<double>, double> GetAbsoluteError(
        const std::vector<ProductionData>& measuredFacilityProdData,
        const std::vector<ProductionData>& calculatedFacilityProdData) {
        
        std::vector<double> errorList;
        double averageError = 0.0;
        size_t lent = measuredFacilityProdData.size();
        
        for (size_t i = 0; i < lent; i++) {
            double error = std::abs(measuredFacilityProdData[i].MonthlyLiquidProduced -
                calculatedFacilityProdData[i].MonthlyLiquidProduced);
            errorList.push_back(error);
            averageError += error;
        }

        averageError /= static_cast<double>(lent);

        return {errorList, averageError};
    }

    std::tuple<std::vector<std::vector<ProductionData>>,
               std::vector<std::vector<WellTestData>>,
               std::vector<std::vector<ProductionData>>,
               std::vector<double>,
               double> 
    AllocationMethod1(
        const std::vector<ProductionData>& allProdData,
        const std::string& timeFrequency,
        const std::vector<WellTestData>& listOfWellTestData,
        double trunkLineReconciliationFactor,
        const std::string& allocationMethod) {
        
        auto [_, __, drainagePointNames] = assetExplorerGeneration.GetUniqueData(allProdData);
        std::vector<Date> dates = assetExplorerGeneration.GetListOfYears1(allProdData, timeFrequency);
        
        auto productionDataList = GetProductionDataReadingsDrainagePointsLevel(allProdData,
            dates, timeFrequency, drainagePointNames, allocationMethod);
        
        auto wellTestDataList = wellTestDataAnalysis.GetWellTestDataDrainagePointsLevel(listOfWellTestData,
            dates, timeFrequency, drainagePointNames, productionDataList);

        auto facilityProductionData = backAllocate.GetMonthlyProductionDataHighNodeLevel(
            allProdData, dates, trunkLineReconciliationFactor);

        auto reconciledProductionDataList = GetReconciledProductionDataDrainagePointsLevel(
            productionDataList, wellTestDataList, dates, timeFrequency, trunkLineReconciliationFactor);

        auto reconciledFacilityData = GetMonthlyProdDataDataHighNodeLevel(reconciledProductionDataList, dates);

        auto [errorList, averageError] = GetAbsoluteError(facilityProductionData, reconciledFacilityData);

        return {productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError};
    }

    std::tuple<std::vector<std::vector<ProductionData>>,
               std::vector<std::vector<WellTestData>>,
               std::vector<std::vector<ProductionData>>,
               std::vector<double>,
               double> 
    AllocationMethod2(
        const std::vector<ProductionData>& allProdData,
        const std::string& timeFrequency,
        const std::vector<WellTestData>& listOfWellTestData,
        double trunkLineReconciliationFactor,
        const std::string& allocationMethod,
        const std::vector<ProductionData>& facilityDailyProdDataList) {
        
        auto [_, __, drainagePointNames] = assetExplorerGeneration.GetUniqueData(allProdData);
        std::vector<Date> dates = assetExplorerGeneration.GetListOfYears1(allProdData, timeFrequency);
        
        auto productionDataList = GetProductionDataReadingsDrainagePointsLevel(allProdData,
            dates, timeFrequency, drainagePointNames, allocationMethod);
        
        auto wellTestDataList = wellTestDataAnalysis.GetWellTestDataDrainagePointsLevel(listOfWellTestData,
            dates, timeFrequency, drainagePointNames, productionDataList);

        auto facilityWellTestData = wellTestDataAnalysis.GetMonthlyWellTestDataHighNodeLevel(wellTestDataList, dates);

        auto facilityProductionData = backAllocate.GetMonthlyProductionDataHighNodeLevel(
            facilityDailyProdDataList, dates, trunkLineReconciliationFactor);

        auto reconciledProductionDataList = GetReconciledProductionDataDrainagePointsLevel2(
            productionDataList, wellTestDataList, dates, timeFrequency,
            facilityProductionData, facilityWellTestData);

        auto reconciledFacilityData = GetMonthlyProdDataDataHighNodeLevel(reconciledProductionDataList, dates);

        auto [errorList, averageError] = GetAbsoluteError(facilityProductionData, reconciledFacilityData);

        return {productionDataList, wellTestDataList, reconciledProductionDataList, errorList, averageError};
    }
};