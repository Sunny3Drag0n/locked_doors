#ifndef SOLUTION_H
#define SOLUTION_H

#include "datetime.h"
#include <optional>
#include <vector>

Date currentDate; ///< date
int currentTime;  ///< hours

class SecurityLevel {
  public:
    SecurityLevel() {}
    SecurityLevel(int lvl) : level(lvl) {}
    bool operator<=(const SecurityLevel &other) const {
        return !level.has_value() ||
               (level.has_value() && other.level.has_value() &&
                level.value() <= other.level.value());
    }

  private:
    std::optional<int> level;
};

class Key {
  public:
    Key(SecurityLevel lvl) : lvl(lvl) {}
    bool canAccess(const SecurityLevel &locationSecLevel) const {
        return locationSecLevel <= lvl;
    }

  private:
    SecurityLevel lvl;
};

class Door {
  public:
    Door(SecurityLevel lvl) : lvl(lvl) {}
    Door(SecurityLevel lvl, std::vector<TimeInterval> allowed, std::vector<TimeInterval> forbiden, std::vector<DateInterval> forbiddenDates) 
    : lvl(lvl), allowedTimeIntervals(allowed), forbiddenTimeIntervals(forbiden), forbiddenDateIntervals(forbiddenDates) {}
    void setAllowedTimeIntervals(std::vector<TimeInterval> intervals) {
        allowedTimeIntervals = intervals;
    }
    void setForbiddenTimeIntervals(std::vector<TimeInterval> intervals) {
        forbiddenTimeIntervals = intervals;
    }
    void setForbiddenDateIntervals(std::vector<DateInterval> intervals) {
        forbiddenDateIntervals = intervals;
    }
    bool tryOpen(const Key &key) const {
        for (const auto &interval : forbiddenDateIntervals) {
            if (interval.contain(currentDate)) {
                return false;
            }
        }
        for (const auto &interval : forbiddenTimeIntervals) {
            if (interval.contain(currentTime)) {
                return false;
            }
        }
        for (const auto &interval : allowedTimeIntervals) {
            if (interval.contain(currentTime)) {
                return key.canAccess(lvl);
            }
        }
        return false;
    }

  private:
    std::vector<TimeInterval> allowedTimeIntervals;
    std::vector<TimeInterval> forbiddenTimeIntervals;
    std::vector<DateInterval> forbiddenDateIntervals;
    SecurityLevel lvl;
};

#endif