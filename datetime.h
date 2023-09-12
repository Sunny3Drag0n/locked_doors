#ifndef DATETIME_H
#define DATETIME_H

struct TimeInterval {
    int first;
    int last;
    bool contain(int current) const {
        if (first <= last) {
            return first <= current && current <= last;
        } else {
            return !(last < current && current < first);
        }
    }
};

struct Date {
    int day;
    int month;
    bool operator<=(const Date &other) const {
        if (month <= other.month) {
            if (month == other.month) {
                return day <= other.day;
            } else {
                return true;
            }
        }
        return false;
    }
    bool operator<(const Date &other) const {
        if (month == other.month) {
            return day <= other.day;
        }
        return month < other.month;
    }
};

struct DateInterval {
    Date first;
    Date last;
    bool contain(const Date &current) const {
        if (first < last) {
            return first <= current && current <= last;
        } else {
            return last <= current || current <= first;
        }
    }
};

#endif
