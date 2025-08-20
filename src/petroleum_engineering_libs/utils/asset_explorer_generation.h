#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

// --- Basic supporting structs (stubs, adjust as needed) ---
struct Date {
    int Day;
    int Month;
    int Year;
};

struct ProductionData {
    std::string DrainagePoint;
    std::string Reservoir;
    std::string Field;
    std::string Lease;
    std::string TubingString;
    std::string FacilityName;

    int Day;
    int Month;
    int Year;

    double CondensateGasRatio;
    double CumulativeGasInjected;
    double CumulativeOilProduced;
    double CumulativeLiquidProduced;
    double UltimateRecovery;
    double MonthlyGasCalendarDaysRate;
    double MonthlyGasInjected;
    double MonthlyGasInjectionCalendarDaysRate;
    double MonthlyGasInjectionProdDaysRate;
    double MonthlyGasProdDaysRate;
    double MonthlyGasProduced;
    double MonthlyLiquidCalendarDaysRate;
    double MonthlyLiquidProdDaysRate;
    double MonthlyLiquidProduced;
    double MonthlyOilCalendarDaysRate;
    double MonthlyOilProdDaysRate;
    double MonthlyOilProduced;
    double MonthlyProdBean;
    double MonthlyProdSand;
    double MonthlyProdTHP;
    double MonthlyWaterCalendarDaysRate;
    double MonthlyWaterInjected;
    double MonthlyWaterInjectionCalendarDaysRate;
    double MonthlyWaterInjectionProdDaysRate;
    double MonthlyWaterProdDaysRate;
    double MonthlyWaterProduced;
    double ProdDays;
    double ProdGOR;
    double WaterCut;
    double WaterGasRatio;
    double LiquidProduced;
    double ProdHours;
    double DefermentFactor;
    double SplitFactor;
};

// --- Tree data structures ---
struct DrainagePointProductionData {
    std::string Label;
    std::string Icon;
    std::string ProductionDataList;
};

struct ReservoirProductionData {
    std::string Label;
    std::string Icon;
    std::vector<DrainagePointProductionData> Children;
};

struct FieldProductionData {
    std::string Label;
    std::string Icon;
    std::vector<ReservoirProductionData> Children;
};

// --- Utility class ---
class AssetExplorerGeneration {
public:
    // Example stub: you’d implement sorting logic here
    struct DateCreation {
        std::vector<Date> SortDate(const std::vector<Date>& dates) {
            auto sorted = dates;
            std::sort(sorted.begin(), sorted.end(), [](const Date& a, const Date& b) {
                if (a.Year != b.Year) return a.Year < b.Year;
                if (a.Month != b.Month) return a.Month < b.Month;
                return a.Day < b.Day;
            });
            return sorted;
        }
    };

    DateCreation dateCreation;

    bool IsContainsText(const std::vector<std::string>& texts, const std::string& text) const {
        for (const auto& t : texts) {
            if (t == text) return true;
        }
        return false;
    }

    std::string ConvertFloat64ToString(double x) const {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(6) << x;
        return oss.str();
    }

    std::string ConvertIntToString(int x) const {
        return std::to_string(x);
    }

    std::string GetRow(const ProductionData& r, bool isLastRow) const {
        const std::string columnDelimiter = "@#$%";
        const std::string rowDelimiter = "@#*$%";

        std::string uniqueId = r.DrainagePoint + r.Reservoir + r.Field + r.Lease;

        std::string lastrow = ConvertIntToString(r.Year) + rowDelimiter;
        if (isLastRow) {
            lastrow = ConvertIntToString(r.Year);
        }

        std::string date = ConvertIntToString(r.Day) + "/" +
                           ConvertIntToString(r.Month) + "/" +
                           ConvertIntToString(r.Year);

        std::string row = uniqueId + columnDelimiter +
            ConvertFloat64ToString(r.CondensateGasRatio) + columnDelimiter +
            ConvertFloat64ToString(r.CumulativeGasInjected) + columnDelimiter +
            ConvertFloat64ToString(r.CumulativeOilProduced) + columnDelimiter +
            ConvertFloat64ToString(r.CumulativeLiquidProduced) + columnDelimiter +
            ConvertFloat64ToString(r.UltimateRecovery) + columnDelimiter +
            ConvertIntToString(r.Day) + columnDelimiter +
            r.DrainagePoint + columnDelimiter +
            r.Field + columnDelimiter +
            r.Lease + columnDelimiter +
            ConvertIntToString(r.Month) + columnDelimiter +
            date + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasInjected) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasInjectionCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasInjectionProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyGasProduced) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyLiquidCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyLiquidProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyLiquidProduced) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyOilCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyOilProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyOilProduced) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyProdBean) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyProdSand) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyProdTHP) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterInjected) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterInjectionCalendarDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterInjectionProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterProdDaysRate) + columnDelimiter +
            ConvertFloat64ToString(r.MonthlyWaterProduced) + columnDelimiter +
            ConvertFloat64ToString(r.ProdDays) + columnDelimiter +
            ConvertFloat64ToString(r.ProdGOR) + columnDelimiter +
            r.Reservoir + columnDelimiter +
            r.TubingString + columnDelimiter +
            ConvertFloat64ToString(r.WaterCut) + columnDelimiter +
            ConvertFloat64ToString(r.WaterGasRatio) + columnDelimiter +
            lastrow;

        return row;
    }

    bool isContainProductionDateYearly(const std::vector<Date>& dates, int year) const {
        for (const auto& d : dates) {
            if (d.Year == year) return true;
        }
        return false;
    }

    bool isContainProductionDateMonthly(const std::vector<Date>& dates, int year, int month) const {
        for (const auto& d : dates) {
            if (d.Year == year && d.Month == month) return true;
        }
        return false;
    }

    bool isContainProductionDateDaily(const std::vector<Date>& dates, int year, int month, int day) const {
        for (const auto& d : dates) {
            if (d.Year == year && d.Month == month && d.Day == day) return true;
        }
        return false;
    }

    std::vector<Date> GetListOfYears1(const std::vector<ProductionData>& listOfProductionData, const std::string& timeFrequency) {
        std::vector<Date> dates;
        for (const auto& pd : listOfProductionData) {
            if (timeFrequency == "yearly") {
                if (!isContainProductionDateYearly(dates, pd.Year)) {
                    dates.push_back({31, 12, pd.Year});
                }
            } else if (timeFrequency == "monthly") {
                if (!isContainProductionDateMonthly(dates, pd.Year, pd.Month)) {
                    dates.push_back({28, pd.Month, pd.Year});
                }
            } else if (timeFrequency == "daily") {
                if (!isContainProductionDateDaily(dates, pd.Year, pd.Month, pd.Day)) {
                    dates.push_back({pd.Day, pd.Month, pd.Year});
                }
            }
        }
        return dateCreation.SortDate(dates);
    }

    std::tuple<std::vector<std::string>, std::vector<std::string>, std::vector<std::string>>
    GetUniqueData(const std::vector<ProductionData>& productionDataList) {
        std::vector<std::string> fieldNames, reservoirNames, drainagePointNames;
        for (const auto& pd : productionDataList) {
            if (!IsContainsText(fieldNames, pd.Field)) fieldNames.push_back(pd.Field);
            if (!IsContainsText(reservoirNames, pd.Reservoir)) reservoirNames.push_back(pd.Reservoir);
            if (!IsContainsText(drainagePointNames, pd.DrainagePoint)) drainagePointNames.push_back(pd.DrainagePoint);
        }
        return {fieldNames, reservoirNames, drainagePointNames};
    }

    std::vector<FieldProductionData> CreateAssetsExplorer(std::vector<ProductionData> productionDataList2,
                                                          const std::string& drainagePointNameFormat) {
        const std::string delimiter = "@";
        std::vector<std::string> drainagePointFormaTexts;
        size_t start = 0, end;
        while ((end = drainagePointNameFormat.find(delimiter, start)) != std::string::npos) {
            drainagePointFormaTexts.push_back(drainagePointNameFormat.substr(start, end - start));
            start = end + delimiter.length();
        }
        if (start < drainagePointNameFormat.size()) {
            drainagePointFormaTexts.push_back(drainagePointNameFormat.substr(start));
        }

        std::vector<ProductionData> productionDataList = productionDataList2;
        for (auto& pd : productionDataList) {
            pd.DrainagePoint = pd.Field + pd.TubingString + ":" + pd.Reservoir;
            if (!drainagePointFormaTexts.empty()) {
                pd.DrainagePoint.clear();
            }
            for (const auto& token : drainagePointFormaTexts) {
                if (token == "Field") pd.DrainagePoint += pd.Field;
                else if (token == "Reservoir") pd.DrainagePoint += pd.Reservoir;
                else if (token == "String") pd.DrainagePoint += pd.TubingString;
                else if (token == "OML") pd.DrainagePoint += pd.Lease;
                else pd.DrainagePoint += token;
            }
        }

        auto [fieldNames, reservoirNames, drainagePointNames] = GetUniqueData(productionDataList);

        std::vector<FieldProductionData> fields;
        for (const auto& field : fieldNames) {
            std::vector<ReservoirProductionData> reservoirs;
            for (const auto& res : reservoirNames) {
                std::vector<DrainagePointProductionData> drainagePoints;
                for (const auto& dp : drainagePointNames) {
                    std::vector<ProductionData> prodDataList;
                    for (const auto& pd : productionDataList) {
                        if (pd.Field == field && pd.Reservoir == res && pd.DrainagePoint == dp) {
                            prodDataList.push_back(pd);
                        }
                    }
                    if (!prodDataList.empty()) {
                        std::string table;
                        for (size_t l = 0; l < prodDataList.size(); ++l) {
                            table += GetRow(prodDataList[l], l == prodDataList.size() - 1);
                        }
                        drainagePoints.push_back({dp, "", table});
                    }
                }
                if (!drainagePoints.empty()) {
                    reservoirs.push_back({res, "", drainagePoints});
                }
            }
            if (!reservoirs.empty()) {
                FieldProductionData fieldData{field, "", reservoirs};
                fields.push_back(fieldData);
            }
        }
        return fields;
    }
};