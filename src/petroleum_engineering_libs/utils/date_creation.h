#include <iostream>
#include <vector>
#include <algorithm>
#include "src/petroleum_engineering_libs/models/date.h"

class DateCreation {
public:
    bool Compare(const Date& d1, const Date& d2) {
        if (d1.Year < d2.Year) return true;
        if (d1.Year == d2.Year && d1.Month < d2.Month) return true;
        if (d1.Year == d2.Year && d1.Month == d2.Month && d1.Day < d2.Day) return true;
        return false;
    }

    bool EqualTo(const Date& d1, const Date& d2) {
        return (d1.Year == d2.Year && d1.Month == d2.Month && d1.Day == d2.Day);
    }

    bool EqualMonthYear(const Date& d1, const Date& d2) {
        return (d1.Year == d2.Year && d1.Month == d2.Month);
    }

    Date GetMinimumDate(const Date& d1, const Date& d2) {
        return Compare(d1, d2) ? d1 : d2;
    }

    Date GetMaximumDate(const Date& d1, const Date& d2) {
        return Compare(d1, d2) ? d2 : d1;
    }

    bool IsMinimumDate(const Date& d1, const Date& d2) {
        return Compare(d1, d2);
    }

    bool IsMaximumDate(const Date& d1, const Date& d2) {
        return !Compare(d1, d2);
    }

    bool IsContainsDate(const std::vector<Date>& dates, const Date& d1) {
        for (const auto& d : dates) {
            if (EqualTo(d, d1)) return true;
        }
        return false;
    }

    Date DateIncrementByMonth(const Date& d1) {
        Date d2 = d1;
        switch (d2.Month) {
            case 1: d2.Month++; if (d2.Day > 28) d2.Day = 28; break;
            case 2: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 3: d2.Month++; if (d2.Day > 30) d2.Day = 30; break;
            case 4: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 5: d2.Month++; if (d2.Day > 30) d2.Day = 30; break;
            case 6: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 7: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 8: d2.Month++; if (d2.Day > 30) d2.Day = 30; break;
            case 9: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 10: d2.Month++; if (d2.Day > 30) d2.Day = 30; break;
            case 11: d2.Month++; if (d2.Day > 31) d2.Day = 31; break;
            case 12: d2.Month = 1; d2.Year++; if (d2.Day > 31) d2.Day = 31; break;
        }
        return d2;
    }

    Date DateIncrementByYears(const Date& d1, int numberOfYears) {
        Date d2 = d1;
        d2.Year += numberOfYears;
        return d2;
    }

    std::vector<Date> SortDate(std::vector<Date> dates) {
        std::sort(dates.begin(), dates.end(), [&](const Date& a, const Date& b) {
            return Compare(a, b);
        });
        return dates;
    }

    int DaysInMonth(int month) {
        switch (month) {
            case 1: return 31;
            case 2: return 28;
            case 3: return 31;
            case 4: return 30;
            case 5: return 31;
            case 6: return 30;
            case 7: return 31;
            case 8: return 31;
            case 9: return 30;
            case 10: return 31;
            case 11: return 30;
            case 12: return 31;
            default: return 0;
        }
    }

    int DateDiff_TotalDays(const Date& d1, const Date& d2) {
        int days = 0;

        if (d1.Year > d2.Year) {
            for (int i = d2.Year; i < d1.Year; i++) {
                days += (i % 4 == 0) ? 366 : 365;
            }
        } else {
            for (int i = d1.Year; i < d2.Year; i++) {
                days -= (i % 4 == 0) ? 366 : 365;
            }
        }

        if (d1.Month > d2.Month) {
            for (int i = d2.Month; i < d1.Month; i++) {
                days += DaysInMonth(i);
            }
        } else {
            for (int i = d1.Month; i < d2.Month; i++) {
                days -= DaysInMonth(i);
            }
        }

        if (d1.Day > d2.Day) {
            days += (d1.Day - d2.Day);
        } else {
            days -= (d2.Day - d1.Day);
        }

        return days;
    }

    std::vector<int> GetDaysList(const Date& StartDate, const std::vector<Date>& dateTimes) {
        std::vector<int> daysList;
        for (const auto& d : dateTimes) {
            daysList.push_back(DateDiff_TotalDays(d, StartDate));
        }
        return daysList;
    }
};