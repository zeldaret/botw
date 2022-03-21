/**
 * @file time.h
 * @brief Time implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
class TimeSpan {
public:
    u64 nanoseconds;

    static TimeSpan FromNanoSeconds(u64 nanoSeconds) {
        TimeSpan ret;
        ret.nanoseconds = nanoSeconds;
        return ret;
    }

    static TimeSpan FromSeconds(u64 seconds) {
        return FromNanoSeconds(seconds * 1000 * 1000 * 1000);
    }
    static TimeSpan FromMinutes(u64 minutes) {
        return FromNanoSeconds(minutes * 1000 * 1000 * 1000 * 60);
    }
    static TimeSpan FromHours(u64 hours) {
        return FromNanoSeconds(hours * 1000 * 1000 * 1000 * 60 * 60);
    }
    static TimeSpan FromDays(u64 days) {
        return FromNanoSeconds(days * 1000 * 1000 * 1000 * 60 * 60 * 24);
    }
};

namespace time {

Result Initialize();
bool IsInitialized();

struct CalendarTime {
    s16 year;
    s8 month;
    s8 day;
    s8 hour;
    s8 minute;
    s8 second;
};

enum DayOfTheWeek { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

struct TimeZone {
    char standardTimeName[0x8];
    bool _9;        // daylight savings or something?
    s32 utcOffset;  // in seconds
};

struct CalendarAdditionalInfo {
    nn::time::DayOfTheWeek dayOfTheWeek;
    s32 dayofYear;
    nn::time::TimeZone timeZone;
};

struct PosixTime {
    u64 time;
};

class StandardUserSystemClock {
public:
    static Result GetCurrentTime(nn::time::PosixTime*);
};

struct TimeZoneRule;  // shrug

Result ToCalendarTime(nn::time::CalendarTime*, nn::time::CalendarAdditionalInfo*,
                      nn::time::PosixTime const&);
Result ToCalendarTime(nn::time::CalendarTime*, nn::time::CalendarAdditionalInfo*,
                      nn::time::PosixTime const&, nn::time::TimeZoneRule const&);
Result ToPosixTime(int*, PosixTime*, int, const CalendarTime&);
CalendarTime ToCalendarTimeInUtc(const PosixTime&);
PosixTime ToPosixTimeFromUtc(const CalendarTime&);
};  // namespace time
};  // namespace nn
