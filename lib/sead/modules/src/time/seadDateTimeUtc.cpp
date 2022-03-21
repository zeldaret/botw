#ifdef NNSDK
#include <nn/time.h>
#else
#error "Unknown platform"
#endif

#include "basis/seadRawPrint.h"
#include "time/seadDateTime.h"
#include "time/seadDateUtil.h"

namespace sead
{
DateTimeUtc::DateTimeUtc(u64 unix_time)
{
    mUnixTime = unix_time;
}

DateTimeUtc::DateTimeUtc(const DateTime& date_time)
{
    CalendarTime time;
    date_time.getCalendarTime(&time);

#ifdef NNSDK
    // Note: time sysmodule is not initialised here.
    nn::time::CalendarTime nn_time;
    nn_time.year = time.getYear();
    nn_time.month = time.getMonth().getValueOneOrigin();
    nn_time.day = time.getDay();
    nn_time.hour = time.getHour();
    nn_time.minute = time.getMinute();
    nn_time.second = time.getSecond();
    nn::time::PosixTime posix_time;
    int dummy = 0;
    nn::time::ToPosixTime(&dummy, &posix_time, 1, nn_time);
    mUnixTime = posix_time.time;
#endif
}

DateTimeUtc::DateTimeUtc(const CalendarTime& time)
{
    setUnixTime(time);
}

DateTimeUtc::DateTimeUtc(const CalendarTime::Year& year, const CalendarTime::Month& month,
                         const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                         const CalendarTime::Minute& minute, const CalendarTime::Second& second)
{
    setUnixTime(year, month, day, hour, minute, second);
}

u64 DateTimeUtc::setNow()
{
#ifdef NNSDK
    DateTime::initializeSystemTimeModule();
    nn::time::PosixTime now;
    nn::time::StandardUserSystemClock::GetCurrentTime(&now);
    mUnixTime = now.time;
#endif
    return mUnixTime;
}

u64 DateTimeUtc::setUnixTime(const CalendarTime& time)
{
#ifdef NNSDK
    DateTime::initializeSystemTimeModule();
    nn::time::CalendarTime nn_time;
    nn_time.year = time.getYear();
    nn_time.month = time.getMonth().getValueOneOrigin();
    nn_time.day = time.getDay();
    nn_time.hour = time.getHour();
    nn_time.minute = time.getMinute();
    nn_time.second = time.getSecond();
    mUnixTime = nn::time::ToPosixTimeFromUtc(nn_time).time;
#endif
    return mUnixTime;
}

u64 DateTimeUtc::setUnixTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
                             const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                             const CalendarTime::Minute& minute, const CalendarTime::Second& second)
{
    DateTime::initializeSystemTimeModule();
    CalendarTime time(year, month, day, hour, minute, second);
#ifdef NNSDK
    nn::time::CalendarTime nn_time;
    nn_time.year = time.getYear();
    nn_time.month = time.getMonth().getValueOneOrigin();
    nn_time.day = time.getDay();
    nn_time.hour = time.getHour();
    nn_time.minute = time.getMinute();
    nn_time.second = time.getSecond();
    mUnixTime = nn::time::ToPosixTimeFromUtc(nn_time).time;
#endif
    return mUnixTime;
}

void DateTimeUtc::getCalendarTime(CalendarTime* out) const
{
#ifdef NNSDK
    DateTime::initializeSystemTimeModule();
    const nn::time::CalendarTime ctime = nn::time::ToCalendarTimeInUtc({mUnixTime});

    CalendarTime::Date date(ctime.year, CalendarTime::Month::makeFromValueOneOrigin(ctime.month),
                            ctime.day);
    CalendarTime::Time time(ctime.hour, ctime.minute, ctime.second);
#endif

    out->setDate(date);
    out->setTime(time);
}

DateSpan DateTimeUtc::diff(DateTimeUtc time) const
{
    return DateSpan(mUnixTime - time.mUnixTime);
}

DateSpan DateTimeUtc::diffToNow() const
{
    DateTimeUtc now(0);
    now.setNow();
    return now.diff(*this);
}

DateSpan operator-(DateTimeUtc lhs, DateTimeUtc rhs)
{
    return DateSpan(lhs.getUnixTime() - rhs.getUnixTime());
}

DateTimeUtc operator-(DateTimeUtc time, DateSpan span)
{
    return DateTimeUtc(time.getUnixTime() - span.getSpan());
}

DateTimeUtc operator+(DateTimeUtc time, DateSpan span)
{
    return DateTimeUtc(time.getUnixTime() + span.getSpan());
}
}  // namespace sead
