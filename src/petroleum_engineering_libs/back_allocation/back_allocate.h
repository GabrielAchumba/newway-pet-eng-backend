#pragma once

#include <vector>
#include <string>
#include "src/petroleum_engineering_libs/models/date.h"
#include "src/petroleum_engineering_libs/models/production_data.h"
#include "src/petroleum_engineering_libs/models/well_test_data.h"


class BackAllocate {
public:
    bool IsContainsBackAllocate1(const std::vector<ProductionData>& listOfProductionData,
                               const Date& currentDate,
                               const std::string& facilityName) {
        for (const auto& data : listOfProductionData) {
            if (data.Date2.Year == currentDate.Year &&
                data.Date2.Month == currentDate.Month &&
                data.Date2.Day == currentDate.Day &&
                data.FacilityName == facilityName) {
                return true;
            }
        }
        return false;
    }

    bool IsContainsBackAllocate2(const std::vector<WellTestData>& listOfWellTestData,
                               const Date& currentDate,
                               const std::string& facilityName) {
        for (const auto& data : listOfWellTestData) {
            if (data.Date1.Year == currentDate.Year &&
                data.Date1.Month == currentDate.Month &&
                data.Date1.Day == currentDate.Day &&
                data.Facility == facilityName) {
                return true;
            }
        }
        return false;
    }

    std::vector<ProductionData> GetDrainagePointsByFacility(const Date& currentDate,
                                                          const std::string& facilityName,
                                                          const std::vector<ProductionData>& listOfProductionData) {
        std::vector<ProductionData> results;
        for (const auto& data : listOfProductionData) {
            if (!IsContainsBackAllocate1(listOfProductionData, currentDate, facilityName)) {
                results.push_back(data);
            }
        }
        return results;
    }

    std::vector<WellTestData> GetDrainagePointsWellTestDataByFacility(const Date& currentDate,
                                                                     const std::string& facilityName,
                                                                     const std::vector<WellTestData>& listOfWellTestData) {
        std::vector<WellTestData> results;
        for (const auto& data : listOfWellTestData) {
            if (!IsContainsBackAllocate2(listOfWellTestData, currentDate, facilityName)) {
                results.push_back(data);
            }
        }
        return results;
    }

    std::vector<double> SumWellsActualWellTestVolume(const std::vector<WellTestData>& listOfWellTestData) {
        std::vector<double> results;
        double sumGas = 0;
        double sumOil = 0;
        double sumWater = 0;
        double sumLiquid = 0;

        for (const auto& data : listOfWellTestData) {
            sumGas += data.GasNew;
            sumOil += data.OilNew;
            sumWater += data.WaterNew;
            sumLiquid += data.LiquidNew;
        }

        results.push_back(sumGas);
        results.push_back(sumOil);
        results.push_back(sumWater);
        results.push_back(sumLiquid);
        return results;
    }

    std::vector<ProductionData> GetDailyProductionDataHighNodeLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& dailyDates) {
        
        std::vector<ProductionData> results;
        for (const auto& date : dailyDates) {
            ProductionData productionData;
            productionData.Day = date.Day;
            productionData.Month = date.Month;
            productionData.Year = date.Year;

            productionData.Lease = listOfProductionData[0].Lease;
            productionData.Field = listOfProductionData[0].Field;
            productionData.FacilityName = listOfProductionData[0].FacilityName;
            productionData.Reservoir = listOfProductionData[0].Reservoir;
            productionData.TubingString = listOfProductionData[0].TubingString;
            productionData.DrainagePoint = listOfProductionData[0].DrainagePoint;

            results.push_back(productionData);
        }

        for (size_t i = 0; i < results.size(); i++) {
            double facilityLiquidVolume = 0;
            for (const auto& prodData : listOfProductionData) {
                if (results[i].Year == prodData.Year &&
                    results[i].Month == prodData.Month &&
                    results[i].Day == prodData.Day) {
                    facilityLiquidVolume += prodData.LiquidProduced;
                }
            }
            results[i].LiquidProduced = facilityLiquidVolume;
        }

        return results;
    }

    std::vector<ProductionData> GetMonthlyProductionDataHighNodeLevel(
        const std::vector<ProductionData>& listOfProductionData,
        const std::vector<Date>& monthlydates,
        double trunkLineReconciliationFactor) {
        
        std::vector<ProductionData> results;
        for (const auto& date : monthlydates) {
            ProductionData productionData;
            productionData.Day = date.Day;
            productionData.Month = date.Month;
            productionData.Year = date.Year;

            productionData.Lease = listOfProductionData[0].Lease;
            productionData.Field = listOfProductionData[0].Field;
            productionData.FacilityName = listOfProductionData[0].FacilityName;
            productionData.Reservoir = listOfProductionData[0].Reservoir;
            productionData.TubingString = listOfProductionData[0].TubingString;
            productionData.DrainagePoint = listOfProductionData[0].DrainagePoint;

            results.push_back(productionData);
        }

        for (size_t i = 0; i < results.size(); i++) {
            double facilityLiquidVolume = 0;
            for (const auto& prodData : listOfProductionData) {
                if (results[i].Year == prodData.Year &&
                    results[i].Month == prodData.Month) {
                    facilityLiquidVolume += prodData.LiquidProduced;
                }
            }
            results[i].LiquidProduced = facilityLiquidVolume * trunkLineReconciliationFactor;
            results[i].MonthlyLiquidProduced = results[i].LiquidProduced;
        }

        return results;
    }
};