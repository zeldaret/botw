#pragma once

#include "basis/seadTypes.h"
#include "time/seadCalendarTime.h"
#include "time/seadDateSpan.h"

namespace sead
{
class DateTimeUtc;

class DateTime
{
public:
    DateTime(u64 unix_time);
    DateTime(const CalendarTime& time);
    DateTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
             const CalendarTime::Day& day, const CalendarTime::Hour& hour,
             const CalendarTime::Minute& minute, const CalendarTime::Second& second);

    DateTime& operator+=(DateSpan span)
    {
        mUnixTime += span.getSpan();
        return *this;
    }

    DateTime& operator-=(DateSpan span)
    {
        mUnixTime -= span.getSpan();
        return *this;
    }

    u64 setNow();
    void setUnixTime(u64 unix_time) { mUnixTime = unix_time; }
    u64 setUnixTime(const CalendarTime& time);
    u64 setUnixTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
                    const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                    const CalendarTime::Minute& minute, const CalendarTime::Second& second);

    u64 getUnixTime() const { return mUnixTime; }
    void getCalendarTime(CalendarTime* time) const;

    DateSpan diff(DateTime time) const;
    DateSpan diffToNow() const;

    static void initializeSystemTimeModule();

protected:
    static bool mIsInitialized;
    u64 mUnixTime;
};

DateSpan operator-(DateTime lhs, DateTime rhs);
DateTime operator-(DateTime time, DateSpan span);
DateTime operator+(DateTime time, DateSpan span);

class DateTimeUtc
{
public:
    DateTimeUtc(u64 unix_time);
    DateTimeUtc(const DateTime& time);
    DateTimeUtc(const CalendarTime& time);
    DateTimeUtc(const CalendarTime::Year& year, const CalendarTime::Month& month,
                const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                const CalendarTime::Minute& minute, const CalendarTime::Second& second);

    DateTimeUtc& operator+=(DateSpan span)
    {
        mUnixTime += span.getSpan();
        return *this;
    }

    DateTimeUtc& operator-=(DateSpan span)
    {
        mUnixTime -= span.getSpan();
        return *this;
    }

    u64 setNow();
    void setUnixTime(u64 unix_time) { mUnixTime = unix_time; }
    u64 setUnixTime(const CalendarTime& time);
    u64 setUnixTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
                    const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                    const CalendarTime::Minute& minute, const CalendarTime::Second& second);

    u64 getUnixTime() const { return mUnixTime; }
    void getCalendarTime(CalendarTime* time) const;

    DateSpan diff(DateTimeUtc time) const;
    DateSpan diffToNow() const;

protected:
    u64 mUnixTime;
};

DateSpan operator-(DateTimeUtc lhs, DateTimeUtc rhs);
DateTimeUtc operator-(DateTimeUtc time, DateSpan span);
DateTimeUtc operator+(DateTimeUtc time, DateSpan span);
}  // namespace sead
