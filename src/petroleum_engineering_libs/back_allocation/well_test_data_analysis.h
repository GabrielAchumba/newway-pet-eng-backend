#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "src/petroleum_engineering_libs/models/date.h"
#include "src/petroleum_engineering_libs/models/well_test_data.h"
#include "src/petroleum_engineering_libs/models/production_data.h"
#include "src/petroleum_engineering_libs/utils/date_creation.h"


class WellTestDataAnalysis {
private:
    DateCreation dateCreation;

public:
    bool isContainWellTestDataAnalysis1(const std::vector<Date>& dates, int year) {
        for (const auto& date : dates) {
            if (date.Year == year) {
                return true;
            }
        }
        return false;
    }

    bool isContainWellTestDataAnalysis2(const std::vector<Date>& dates, int year, int month) {
        for (const auto& date : dates) {
            if (date.Year == year && date.Month == month) {
                return true;
            }
        }
        return false;
    }

    bool isContainWellTestDataAnalysis3(const std::vector<Date>& dates, int year, int month, int day) {
        for (const auto& date : dates) {
            if (date.Year == year && date.Month == month && date.Day == day) {
                return true;
            }
        }
        return false;
    }

    std::vector<Date> GetListOfYears1(const std::vector<WellTestData>& listOfWellTestData,
                                    const std::string& timeFrequency) {
        std::vector<Date> dates;
        bool check = false;

        for (const auto& wellTestData : listOfWellTestData) {
            if (timeFrequency == "yearly") {
                check = isContainWellTestDataAnalysis1(dates, wellTestData.Year);
                if (!check) {
                    Date date;
                    date.Day = 31;
                    date.Month = 12;
                    date.Year = wellTestData.Year;
                    dates.push_back(date);
                }
            }

            if (timeFrequency == "monthly") {
                check = isContainWellTestDataAnalysis2(dates, wellTestData.Year, wellTestData.Month);
                if (!check) {
                    Date date;
                    date.Day = 28;
                    date.Month = wellTestData.Month;
                    date.Year = wellTestData.Year;
                    dates.push_back(date);
                }
            }

            if (timeFrequency == "daily") {
                check = isContainWellTestDataAnalysis3(dates, wellTestData.Year, wellTestData.Month, wellTestData.Day);
                if (!check) {
                    Date date;
                    date.Day = wellTestData.Day;
                    date.Month = wellTestData.Month;
                    date.Year = wellTestData.Year;
                    dates.push_back(date);
                }
            }
        }

        dates = dateCreation.SortDate(dates);
        return dates;
    }

    std::vector<Date> GetListOfYears2(const std::vector<std::vector<WellTestData>>& allWellTestData,
                                    const std::string& timeFrequency) {
        std::vector<Date> dates;
        bool check = false;
        Date date;

        for (const auto& wellTestDataList : allWellTestData) {
            for (const auto& wellTestData : wellTestDataList) {
                if (timeFrequency == "yearly") {
                    check = isContainWellTestDataAnalysis1(dates, wellTestData.Year);
                    if (!check) {
                        date.Day = 31;
                        date.Month = 12;
                        date.Year = wellTestData.Year;
                        dates.push_back(date);
                    }
                }
                if (timeFrequency == "monthly") {
                    check = isContainWellTestDataAnalysis2(dates, wellTestData.Year, wellTestData.Month);
                    if (!check) {
                        date.Day = 28;
                        date.Month = wellTestData.Month;
                        date.Year = wellTestData.Year;
                        dates.push_back(date);
                    }
                }
                if (timeFrequency == "daily") {
                    check = isContainWellTestDataAnalysis3(dates, wellTestData.Year, wellTestData.Month, wellTestData.Day);
                    if (!check) {
                        date.Day = wellTestData.Day;
                        date.Month = wellTestData.Month;
                        date.Year = wellTestData.Year;
                        dates.push_back(date);
                    }
                }
            }
        }

        dates = dateCreation.SortDate(dates);
        return dates;
    }

    WellTestData GetCurrentWellTestData(const std::vector<WellTestData>& listOfWellTestData,
                                      const Date& currentDate,
                                      const std::string& selectedDrainagePoint) {
        size_t nSize = listOfWellTestData.size();
        WellTestData currentWellTestData;

        if (dateCreation.EqualMonthYear(currentDate, listOfWellTestData[0].Date1) &&
            selectedDrainagePoint == listOfWellTestData[0].DrainagePoint) {
            return listOfWellTestData[0];
        }

        if (dateCreation.IsMinimumDate(currentDate, listOfWellTestData[0].Date1) &&
            selectedDrainagePoint == listOfWellTestData[0].DrainagePoint) {
            return listOfWellTestData[0];
        }

        if (nSize > 1) {
            for (size_t i = 1; i < nSize; i++) {
                if (dateCreation.EqualMonthYear(currentDate, listOfWellTestData[i-1].Date1) &&
                    selectedDrainagePoint == listOfWellTestData[i-1].DrainagePoint) {
                    return listOfWellTestData[i-1];
                }

                if (dateCreation.EqualMonthYear(currentDate, listOfWellTestData[i].Date1) &&
                    selectedDrainagePoint == listOfWellTestData[i].DrainagePoint) {
                    return listOfWellTestData[i];
                }

                if (dateCreation.IsMaximumDate(currentDate, listOfWellTestData[i-1].Date1) &&
                    dateCreation.IsMinimumDate(currentDate, listOfWellTestData[i].Date1) &&
                    selectedDrainagePoint == listOfWellTestData[i-1].DrainagePoint) {
                    return listOfWellTestData[i-1];
                }
            }
        }

        if (dateCreation.IsMaximumDate(currentDate, listOfWellTestData[nSize-1].Date1) &&
            selectedDrainagePoint == listOfWellTestData[nSize-1].DrainagePoint) {
            return listOfWellTestData[nSize-1];
        }

        return currentWellTestData;
    }

    ProductionData GetCurrentProductionData(const std::vector<ProductionData>& listOfProductionData,
                                          const Date& currentDate) {
        size_t nSize = listOfProductionData.size();
        ProductionData currentProductionDataData;

        if (dateCreation.EqualMonthYear(currentDate, listOfProductionData[0].Date2)) {
            return listOfProductionData[0];
        }

        if (dateCreation.IsMinimumDate(currentDate, listOfProductionData[0].Date2)) {
            return listOfProductionData[0];
        }

        if (nSize > 1) {
            for (size_t i = 1; i < nSize; i++) {
                if (dateCreation.EqualMonthYear(currentDate, listOfProductionData[i-1].Date2)) {
                    return listOfProductionData[i-1];
                }

                if (dateCreation.EqualMonthYear(currentDate, listOfProductionData[i].Date2)) {
                    return listOfProductionData[i];
                }

                if (dateCreation.IsMaximumDate(currentDate, listOfProductionData[i-1].Date2) &&
                    dateCreation.IsMinimumDate(currentDate, listOfProductionData[i].Date2)) {
                    return listOfProductionData[i-1];
                }
            }
        }

        if (dateCreation.IsMaximumDate(currentDate, listOfProductionData[nSize-1].Date2)) {
            return listOfProductionData[nSize-1];
        }

        return currentProductionDataData;
    }

    std::vector<WellTestData> GetDailyWellTestDataDrainagePointLevelByProdDays(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates,
        const std::vector<ProductionData>& listOfProductionData,
        const std::string& selectedDrainagePoint) {
        
        std::vector<WellTestData> results;
        for (const auto& date : dates) {
            WellTestData wellTestData = GetCurrentWellTestData(listOfWellTestData, date, selectedDrainagePoint);
            ProductionData prodData = GetCurrentProductionData(listOfProductionData, date);
            
            wellTestData.Day = date.Day;
            wellTestData.Month = date.Month;
            wellTestData.Year = date.Year;
            wellTestData.LiquidNew = wellTestData.DailyLiquidVolume * prodData.ProdDays;
            wellTestData.OilNew = (1 - (wellTestData.WaterCut / 100)) * wellTestData.LiquidNew;
            wellTestData.WaterNew = (wellTestData.WaterCut / 100) * wellTestData.LiquidNew;
            wellTestData.GasNew = wellTestData.OilNew * wellTestData.ProdGOR;
            
            results.push_back(wellTestData);
        }
        return results;
    }

    std::vector<WellTestData> GetDailyWellTestDataDrainagePointLevelByProdHours(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates,
        const std::vector<ProductionData>& listOfProductionData,
        const std::string& selectedDrainagePoint) {
        
        std::vector<WellTestData> results;
        for (const auto& date : dates) {
            ProductionData productionData = GetCurrentProductionData(listOfProductionData, date);
            WellTestData wellTestData = GetCurrentWellTestData(listOfWellTestData, date, selectedDrainagePoint);
            
            wellTestData.Day = date.Day;
            wellTestData.Month = date.Month;
            wellTestData.Year = date.Year;
            wellTestData.LiquidNew = wellTestData.LiquidNew * productionData.ProdHours / 24.0;
            wellTestData.OilNew = (1 - (wellTestData.WaterCut / 100)) * wellTestData.LiquidNew;
            wellTestData.WaterNew = (wellTestData.WaterCut / 100) * wellTestData.LiquidNew;
            wellTestData.GasNew = wellTestData.OilNew * wellTestData.ProdGOR;
            
            results.push_back(wellTestData);
        }
        return results;
    }

    std::vector<WellTestData> GetMonthlyWellTestDrainagePointLevel(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates) {
        
        std::vector<WellTestData> results;
        for (const auto& date : dates) {
            WellTestData wellTestData = listOfWellTestData[0];
            wellTestData.Day = date.Day;
            wellTestData.Month = date.Month;
            wellTestData.Year = date.Year;
            results.push_back(wellTestData);
        }

        for (size_t i = 0; i < results.size(); i++) {
            double dNp = 0;
            double dGp = 0;
            double dWp = 0;
            double dLp = 0;

            for (const auto& wellTestData : listOfWellTestData) {
                if (results[i].Year == wellTestData.Year && results[i].Month == wellTestData.Month) {
                    dNp += wellTestData.OilNew;
                    dGp += wellTestData.GasNew;
                    dWp += wellTestData.WaterNew;
                }
            }

            dLp = dNp + dWp;

            results[i].OilNew = dNp;
            results[i].GasNew = dGp;
            results[i].WaterNew = dWp;
            results[i].LiquidNew = dLp;

            results[i].WaterCut = (dNp + dWp) > 0 ? (dWp * 100) / (dNp + dWp) : 0;
            results[i].ProdGOR = dNp > 0 ? dGp / dNp : 0;
            results[i].CondensateGasRatio = dGp > 0 ? dNp / dGp : 0;
            results[i].WaterGasRatio = dGp > 0 ? dWp / dGp : 0;
        }

        return results;
    }

    std::vector<WellTestData> GetYearlyWellTestDrainagePointLevel(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates) {
        
        std::vector<WellTestData> results;
        for (const auto& date : dates) {
            WellTestData wellTestData = listOfWellTestData[0];
            wellTestData.Day = date.Day;
            wellTestData.Month = date.Month;
            wellTestData.Year = date.Year;
            results.push_back(wellTestData);
        }

        for (size_t i = 0; i < results.size(); i++) {
            double dNp = 0;
            double dGp = 0;
            double dWp = 0;

            for (const auto& wellTestData : listOfWellTestData) {
                if (results[i].Year == wellTestData.Year) {
                    dNp += wellTestData.OilNew;
                    dGp += wellTestData.GasNew;
                    dWp += wellTestData.WaterNew;
                }
            }

            results[i].WaterCut = (dNp + dWp) > 0 ? (dWp * 100) / (dNp + dWp) : 0;
            results[i].ProdGOR = dNp > 0 ? dGp / dNp : 0;
            results[i].CondensateGasRatio = dGp > 0 ? dNp / dGp : 0;
            results[i].WaterGasRatio = dGp > 0 ? dWp / dGp : 0;
        }

        return results;
    }

    std::vector<std::vector<WellTestData>> GetWellTestDataDrainagePointsLevel(
        const std::vector<WellTestData>& listOfWellTestData,
        const std::vector<Date>& dates,
        const std::string& timeFrequency,
        const std::vector<std::string>& drainagePointNames,
        const std::vector<std::vector<ProductionData>>& allProdData) {
        
        std::vector<std::vector<WellTestData>> results;

        for (size_t i = 0; i < drainagePointNames.size(); i++) {
            size_t initialIndex = 0;
            for (size_t j = 0; j < listOfWellTestData.size(); j++) {
                if (drainagePointNames[i] == listOfWellTestData[j].DrainagePoint) {
                    initialIndex = j;
                    break;
                }
            }

            auto wellTestRows = GetDailyWellTestDataDrainagePointLevelByProdDays(
                listOfWellTestData, dates, allProdData[initialIndex], drainagePointNames[i]);

            if (timeFrequency == "yearly") {
                results.push_back(GetYearlyWellTestDrainagePointLevel(listOfWellTestData, dates));
            }
            if (timeFrequency == "monthly") {
                results.push_back(GetMonthlyWellTestDrainagePointLevel(wellTestRows, dates));
            }
        }

        return results;
    }

    std::vector<WellTestData> GetMonthlyWellTestDataHighNodeLevel(
        const std::vector<std::vector<WellTestData>>& listOfWellTesData,
        const std::vector<Date>& monthlydates) {
        
        std::vector<WellTestData> results;
        for (const auto& date : monthlydates) {
            WellTestData wellTestData;
            wellTestData.Day = date.Day;
            wellTestData.Month = date.Month;
            wellTestData.Year = date.Year;

            wellTestData.Lease = listOfWellTesData[0][0].Lease;
            wellTestData.Field = listOfWellTesData[0][0].Field;
            wellTestData.FacilityName = listOfWellTesData[0][0].FacilityName;
            wellTestData.Reservoir = listOfWellTesData[0][0].Reservoir;
            wellTestData.TubingString = listOfWellTesData[0][0].TubingString;
            wellTestData.DrainagePoint = listOfWellTesData[0][0].DrainagePoint;

            results.push_back(wellTestData);
        }

        for (const auto& wellTestDataList : listOfWellTesData) {
            for (size_t j = 0; j < wellTestDataList.size(); j++) {
                results[j].OilNew += wellTestDataList[j].OilNew;
                results[j].WaterNew += wellTestDataList[j].WaterNew;
                results[j].GasNew += wellTestDataList[j].GasNew;
                results[j].LiquidNew += wellTestDataList[j].LiquidNew;
            }
        }

        return results;
    }
};