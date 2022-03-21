#include <basis/seadRawPrint.h>
#include <container/seadSafeArray.h>
#include <time/seadCalendarTime.h>
#include <time/seadDateUtil.h>

namespace sead
{
const CalendarTime::Month CalendarTime::cMonth_Jan = 1;
const CalendarTime::Month CalendarTime::cMonth_Feb = 2;
const CalendarTime::Month CalendarTime::cMonth_Mar = 3;
const CalendarTime::Month CalendarTime::cMonth_Apr = 4;
const CalendarTime::Month CalendarTime::cMonth_May = 5;
const CalendarTime::Month CalendarTime::cMonth_Jun = 6;
const CalendarTime::Month CalendarTime::cMonth_Jul = 7;
const CalendarTime::Month CalendarTime::cMonth_Aug = 8;
const CalendarTime::Month CalendarTime::cMonth_Sep = 9;
const CalendarTime::Month CalendarTime::cMonth_Oct = 10;
const CalendarTime::Month CalendarTime::cMonth_Nov = 11;
const CalendarTime::Month CalendarTime::cMonth_Dec = 12;

const CalendarTime::Year CalendarTime::cDefaultYear = 1970;
const CalendarTime::Month CalendarTime::cDefaultMonth = 1;
const CalendarTime::Day CalendarTime::cDefaultDay = 1;
const CalendarTime::Hour CalendarTime::cDefaultHour = 0;
const CalendarTime::Minute CalendarTime::cDefaultMinute = 0;
const CalendarTime::Second CalendarTime::cDefaultSecond = 0;

void CalendarTime::Year::setValue(u32 year)
{
    mValue = year;
}

CalendarTime::Month::Month(u32 month)
{
    setValueOneOrigin(month);
}

void CalendarTime::Month::setValueOneOrigin(u32 m)
{
    SEAD_ASSERT_MSG(1 <= m && m <= 12, "wrong month. correct range is [1, 12]. your param %d", m);
    mValue = m;
}

s32 CalendarTime::Month::addSelf(u32 rhs)
{
    const s32 val = (s32(rhs) + mValue + -1) % 12;
    mValue = val + 1;
    SEAD_ASSERT(1 <= mValue && mValue <= 12);
    return val;
}

s32 CalendarTime::Month::subSelf(u32 rhs)
{
    const s32 val = (mValue - s32(rhs) % 12 + 12 - 1) % 12u;
    mValue = val + 1;
    SEAD_ASSERT(1 <= mValue && mValue <= 12);
    return val;
}

s32 CalendarTime::Month::sub(CalendarTime::Month rhs) const
{
    return s32(mValue) - rhs.getValueOneOrigin();
}

SafeString CalendarTime::Month::makeStringOneOrigin(u32 m)
{
    SEAD_ASSERT_MSG(1 <= m && m <= 12, "wrong month. correct range is [1, 12]. your param %d", m);
    switch (m)
    {
    case 1:
        return "Jan";
    case 2:
        return "Feb";
    case 3:
        return "Mar";
    case 4:
        return "Apr";
    case 5:
        return "May";
    case 6:
        return "Jun";
    case 7:
        return "Jul";
    case 8:
        return "Aug";
    case 9:
        return "Sep";
    case 10:
        return "Oct";
    case 11:
        return "Nov";
    case 12:
    default:
        return "Dec";
    }
}

CalendarTime::Month CalendarTime::Month::makeFromValueOneOrigin(u32 m)
{
    SEAD_ASSERT(1 <= m && m <= 12);
    return Month(m);
}

void CalendarTime::Day::setValue(u32 day)
{
    SEAD_ASSERT_MSG(1 <= day && day <= 31, "wrong day. correct range is [1, 31]. your param %d",
                    day);
    mValue = day;
}

void CalendarTime::Hour::setValue(u32 hour)
{
    SEAD_ASSERT_MSG(hour <= 23, "wrong hour. correct range is [0, 23]. your param %d", hour);
    mValue = hour;
}

void CalendarTime::Minute::setValue(u32 minute)
{
    SEAD_ASSERT_MSG(minute <= 59, "wrong minute. correct range is [0, 59]. your param %d", minute);
    mValue = minute;
}

void CalendarTime::Second::setValue(u32 second)
{
    SEAD_ASSERT_MSG(second <= 59, "wrong day. correct range is [0, 59]. your param %d", second);
    mValue = second;
}

CalendarTime::Date::Date(const CalendarTime::Year& y, const CalendarTime::Month& m,
                         const CalendarTime::Day& d)
    : mYear(y), mMonth(m), mDay(d)
{
    mWeek = DateUtil::calcWeekDay(y, m, d);
}

CalendarTime::Time::Time(const CalendarTime::Hour& h, const CalendarTime::Minute& m,
                         const CalendarTime::Second& s)
    : mHour(h), mMinute(m), mSecond(s)
{
}

CalendarTime::CalendarTime(const CalendarTime::Date& date, const CalendarTime::Time& time)
    : mDate(date), mTime(time)
{
}

CalendarTime::CalendarTime(const CalendarTime::Year& y, const CalendarTime::Month& m,
                           const CalendarTime::Day& d, const CalendarTime::Hour& hour,
                           const CalendarTime::Minute& minute, const CalendarTime::Second& second)
    : mDate(y, m, d), mTime(hour, minute, second)
{
}

void CalendarTime::setDate(const CalendarTime::Date& date)
{
    mDate = date;
    mDate.calcWeek();
}

u32 CalendarTime::getYearDays() const
{
    const u32 m = mDate.mMonth.getValueOneOrigin();
    SEAD_ASSERT_MSG(1 <= m && m <= 12, "wrong month. correct range is [1, 12]. your param %d", m);

    static const u32 sCumulativeNumberOfDays[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
    };
    u32 num_days = mDate.mDay.getValue() + sCumulativeNumberOfDays[m - 1];

    if (m >= 3)
        num_days += DateUtil::isLeapYear(mDate.mYear.getValue());

    return num_days;
}

void CalendarTime::Date::calcWeek()
{
    mWeek = DateUtil::calcWeekDay(mYear, mMonth, mDay);
}

void CalendarTime::makeWeekDayNameLabel_(BufferedSafeString* out_str, CalendarTime::Week week)
{
    static const SafeArray<const char*, 7> labels = {{"日", "月", "火", "水", "木", "金", "土"}};
    out_str->format("曜日:%s", labels[s32(week)]);
}

}  // namespace sead
