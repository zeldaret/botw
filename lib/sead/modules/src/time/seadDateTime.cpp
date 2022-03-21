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
namespace
{
constexpr u32 sDaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
constexpr u32 sDaysSinceJan1[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

u32 convertCalendarDateToDaysSince1970(const CalendarTime::Date& date)
{
    // 0-indexed day.
    const u32 d0 = date.mDay.getValue() - 1;

    const u32 m = date.mMonth.getValueOneOrigin();
    SEAD_ASSERT_MSG(1 <= m && m <= 12, "wrong month. correct range is [1, 12]. your param %d", m);

    const u32 y = date.mYear.getValue();
    SEAD_ASSERT_MSG(y >= 1970, "wrong year. your param %d, must after 1970.", y);

    const u32 days_since_jan1 = sDaysSinceJan1[m - 1];

    u32 num_days = d0 + days_since_jan1;
    if (m >= 3 && DateUtil::isLeapYear(date.mYear.getValue()))
        num_days = d0 + days_since_jan1 + 1;

    u32 num_days_since_1970 = num_days + 365 * (date.mYear.getValue() - 1970);
    if (date.mYear.getValue() > 1970)
    {
        u32 year = 1970;
        do
        {
            num_days_since_1970 += DateUtil::isLeapYear(year);
            ++year;
        } while (year < date.mYear.getValue());
    }

    return num_days_since_1970;
}

u64 convertCalendarTimeToSeconds(const CalendarTime::Time& time)
{
    return 60 * (60 * time.mHour.getValue() + time.mMinute.getValue()) + time.mSecond.getValue();
}

u64 convertCalendarDateTimeToSeconds(const CalendarTime::Date& date, const CalendarTime::Time& time)
{
    const u32 y = date.mYear.getValue();

    const s32 m = date.mMonth.getValueOneOrigin();
    const u32 m_idx = m - 1;
    SEAD_ASSERT_MSG(1 <= m && m <= 12, "wrong month. correct range is [1, 12]. your param %d", m);

    u32 num_days;
    if (m == 2 && DateUtil::isLeapYear(y))
        num_days = sDaysOfMonth[m_idx] + 1;
    else
        num_days = sDaysOfMonth[m_idx];

    const u32 d = date.mDay.getValue();
    SEAD_ASSERT_MSG(d <= num_days, "wrong day, correct range is [1, %d] (when year %4d month %2d)",
                    num_days, y, m);

    const u32 days_since_1970 = convertCalendarDateToDaysSince1970(date);
    return 3600 * 24 * days_since_1970 + convertCalendarTimeToSeconds(time);
}

u32 convertDaysToYears(u32* days)
{
    u32 days_to_remove;
    u32 i = 0;
    u32 year = 1969;
    do
    {
        ++year;
        days_to_remove = i;
        i += DateUtil::isLeapYear(year) ? 366 : 365;
    } while (i <= *days);
    *days -= days_to_remove;
    return year;
}

s32 convertDaysToMonth(u32* days, u32 year)
{
    SEAD_ASSERT_MSG(*days <= 365, "wrong days. correct range is [0, 365]. your param %d", *days);
    u32 days_to_remove;
    u32 month_idx = 0;
    u32 i = 0;
    do
    {
        days_to_remove = i;
        i += (month_idx == 1 && DateUtil::isLeapYear(year)) ? 29 : sDaysOfMonth[month_idx];
        if (*days < i)
            break;
        ++month_idx;
    } while (month_idx < 12);
    *days -= days_to_remove - 1;
    return 1 + month_idx;
}
}  // namespace

bool DateTime::mIsInitialized = false;

DateTime::DateTime(u64 unix_time)
{
    mUnixTime = unix_time;
}

DateTime::DateTime(const CalendarTime& time)
{
    setUnixTime(time);
}

DateTime::DateTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
                   const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                   const CalendarTime::Minute& minute, const CalendarTime::Second& second)
{
    setUnixTime(year, month, day, hour, minute, second);
}

u64 DateTime::setNow()
{
#ifdef NNSDK
    initializeSystemTimeModule();

    nn::time::PosixTime now;
    nn::time::CalendarTime ctime;
    nn::time::StandardUserSystemClock::GetCurrentTime(&now);
    nn::time::ToCalendarTime(&ctime, nullptr, now);

    const auto year = CalendarTime::Year(ctime.year);
    const auto month = CalendarTime::Month::makeFromValueOneOrigin(ctime.month);
    const auto day = CalendarTime::Day(ctime.day);
    const auto hour = CalendarTime::Hour(ctime.hour);
    const auto minute = CalendarTime::Minute(ctime.minute);
    const auto second = CalendarTime::Second(ctime.second);
    setUnixTime(year, month, day, hour, minute, second);
#endif
    return mUnixTime;
}

u64 DateTime::setUnixTime(const CalendarTime& time)
{
    mUnixTime = convertCalendarDateTimeToSeconds(time.getDate(), time.getTime());
    return mUnixTime;
}

u64 DateTime::setUnixTime(const CalendarTime::Year& year, const CalendarTime::Month& month,
                          const CalendarTime::Day& day, const CalendarTime::Hour& hour,
                          const CalendarTime::Minute& minute, const CalendarTime::Second& second)
{
    CalendarTime::Date date(year, month, day);
    CalendarTime::Time time(hour, minute, second);
    mUnixTime = convertCalendarDateTimeToSeconds(date, time);
    return mUnixTime;
}

void DateTime::getCalendarTime(CalendarTime* calendar) const
{
    u32 d = mUnixTime / (3600 * 24);
    const u32 y = convertDaysToYears(&d);
    const u32 m = convertDaysToMonth(&d, y);

    CalendarTime::Time time;
    const auto reduced_time = mUnixTime % (3600 * 24);
    time.mHour.setValue(reduced_time / 3600);
    time.mMinute.setValue((reduced_time % 3600) / 60);
    time.mSecond.setValue(reduced_time % 60);

    if (calendar)
    {
        calendar->setDate(CalendarTime::Date(y, CalendarTime::Month::makeFromValueOneOrigin(m), d));
        calendar->setTime(time);
    }
}

DateSpan DateTime::diff(DateTime time) const
{
    return DateSpan(mUnixTime - time.mUnixTime);
}

DateSpan DateTime::diffToNow() const
{
    DateTime now(0);
    now.setNow();
    return now.diff(*this);
}

void DateTime::initializeSystemTimeModule()
{
    if (mIsInitialized)
        return;

#ifdef NNSDK
    if (!nn::time::IsInitialized())
        nn::time::Initialize();
#endif

    mIsInitialized = true;
}

DateSpan operator-(DateTime lhs, DateTime rhs)
{
    return DateSpan(lhs.getUnixTime() - rhs.getUnixTime());
}

DateTime operator-(DateTime time, DateSpan span)
{
    return DateTime(time.getUnixTime() - span.getSpan());
}

DateTime operator+(DateTime time, DateSpan span)
{
    return DateTime(time.getUnixTime() + span.getSpan());
}
}  // namespace sead
