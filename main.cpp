#include "solution.h"
#include <assert.h>
#include <iostream>
#include <tuple>

/** @brief Проверка условия попадания в интервал */
template <typename InputTyple>
void dateTimeTestTemplate(std::vector<InputTyple> cases) {
    for (auto &[cur, interval, result] : cases) {
        assert(interval.contain(cur) == result);
    }
}

void dateTimeTestCase() {
    using CurTime = int;
    using RequireResult = bool;
    using TimeTestCases = std::tuple<CurTime, TimeInterval, RequireResult>;
    using DateTestCases = std::tuple<Date, DateInterval, RequireResult>;
    dateTimeTestTemplate(std::vector<TimeTestCases>{
        std::make_tuple<CurTime, TimeInterval, RequireResult>(10, {9, 18},
                                                              true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(15, {19, 16},
                                                              true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(10, {19, 16},
                                                              true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(17, {19, 16},
                                                              false),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(10, {18, 6},
                                                              false),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(10, {0, 18},
                                                              true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(10, {18, 0},
                                                              false),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(23, {18, 0},
                                                              true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(0, {18, 0}, true),
        std::make_tuple<CurTime, TimeInterval, RequireResult>(18, {18, 0},
                                                              true),
    });
    std::cout << "TimeInterval tests passed" << std::endl;
    dateTimeTestTemplate(std::vector<DateTestCases>{
        std::make_tuple<Date, DateInterval, RequireResult>(
            {29, 01}, {{17, 01}, {17, 02}}, true),
        std::make_tuple<Date, DateInterval, RequireResult>(
            {16, 01}, {{17, 01}, {17, 02}}, false)});
    std::cout << "DateTestCases tests passed" << std::endl;
}

void securityLvlTestCase() {
    /* Вот тут спорный момент. По логике SecurityLevel() == SecurityLevel(0). Но
     * согласно реализации 0 - уровень, а SecurityLevel() - без уровня
     * безопасности */
    using RequireResult = bool;
    using SecurityLvlTestCases =
        std::tuple<SecurityLevel, SecurityLevel, RequireResult>;
    /** @brief Проверка что условия <= для 2х значений SecurityLevel выполняется
     * корректно */
    for (auto &[first, second, result] : std::vector<SecurityLvlTestCases>{
             {SecurityLevel(), SecurityLevel(), true},
             {SecurityLevel(), SecurityLevel(0), true},
             {SecurityLevel(), SecurityLevel(1), true},
             {SecurityLevel(), SecurityLevel(2), true},
             {SecurityLevel(1), SecurityLevel(1), true},
             {SecurityLevel(2), SecurityLevel(1), false},
             {SecurityLevel(2), SecurityLevel(0), false},
             {SecurityLevel(2), SecurityLevel(), false},
         }) {
        assert((first <= second) == result);
    }
    std::cout << "SecurityLevel tests passed" << std::endl;
    using KeySecurityLvlTestCases =
        std::tuple<Key, SecurityLevel, RequireResult>;
    /** @brief Проверка что ключ (key) может получить доступ к данному уровню
     * (securityLvl) */
    for (auto &[key, securityLvl, result] :
         std::vector<KeySecurityLvlTestCases>{
             {Key(SecurityLevel()), SecurityLevel(), true},
             {Key(SecurityLevel()), SecurityLevel(0), false},
             {Key(SecurityLevel()), SecurityLevel(1), false},
             {Key(SecurityLevel()), SecurityLevel(2), false},
             {Key(SecurityLevel(1)), SecurityLevel(1), true},
             {Key(SecurityLevel(2)), SecurityLevel(1), true},
             {Key(SecurityLevel(2)), SecurityLevel(0), true},
             {Key(SecurityLevel(2)), SecurityLevel(), true},
         }) {
        assert(key.canAccess(securityLvl) == result);
    }
    std::cout << "KeySecurityLevel tests passed" << std::endl;
    using Time = int;
    using OpenDoorTestCases =
        std::tuple<Date, Time, Key, Door, RequireResult>;
    for (auto &[date, time, key, door, result] :
         std::vector<OpenDoorTestCases>{
             {{29,01}, 10, Key(SecurityLevel()), Door(SecurityLevel(), {}, {}, {}), false},
             {{29,01}, 10, Key(SecurityLevel()), Door(SecurityLevel(), {{9,17}}, {}, {}), true},
             {{29,01}, 8, Key(SecurityLevel()), Door(SecurityLevel(), {{9,17}}, {}, {}), false},
             {{29,01}, 19, Key(SecurityLevel()), Door(SecurityLevel(), {{9,17}}, {}, {}), false},
             {{29,01}, 10, Key(SecurityLevel()), Door(SecurityLevel(4), {{9,17}}, {}, {}), false},
             {{29,01}, 10, Key(SecurityLevel(5)), Door(SecurityLevel(4), {{9,17}}, {}, {}), true},
             {{29,01}, 7, Key(SecurityLevel(5)), Door(SecurityLevel(4), {{9,17}}, {}, {}), false},
             {{29,01}, 10, Key(SecurityLevel(5)), Door(SecurityLevel(), {{9,17}}, {{9,12}}, {}), false},
             {{29,01}, 13, Key(SecurityLevel(5)), Door(SecurityLevel(), {{9,17}}, {{9,12}}, {}), true},
             {{29,01}, 10, Key(SecurityLevel(5)), Door(SecurityLevel(), {{9,17}}, {}, {{{20,01},{31,01}}}), false},
             {{29,01}, 10, Key(SecurityLevel(5)), Door(SecurityLevel(), {{9,17}}, {}, {{{20,01},{01,02}}}), false},
         }) {
        currentDate = date;
        currentTime = time;
        assert(door.tryOpen(key) == result);
    }
    std::cout << "OpenDoorTestCases tests passed" << std::endl;
}

int main() {
    dateTimeTestCase();
    securityLvlTestCase();
    return 0;
}
