#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace sead
{
namespace hostio
{
class Context;
class PropertyEvent;
class Reflexible;
}  // namespace hostio

class CalendarTime
{
public:
#define SEAD_CALENDARTIME_MAKE_CLASS(NAME, VARIABLE_NAME)                                          \
    class NAME                                                                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME(u32 VARIABLE_NAME) { setValue(VARIABLE_NAME); }                                       \
        u32 getValue() const { return mValue; }                                                    \
        void setValue(u32 VARIABLE_NAME);                                                          \
                                                                                                   \
    private:                                                                                       \
        u32 mValue;                                                                                \
    };

    SEAD_CALENDARTIME_MAKE_CLASS(Year, year)
    SEAD_CALENDARTIME_MAKE_CLASS(Day, day)
    SEAD_CALENDARTIME_MAKE_CLASS(Hour, hour)
    SEAD_CALENDARTIME_MAKE_CLASS(Minute, minute)
    SEAD_CALENDARTIME_MAKE_CLASS(Second, second)
#undef SEAD_CALENDARTIME_MAKE_CLASS

    class Month
    {
    public:
        Month(u32 month);

        void setValueOneOrigin(u32 month);
        s32 getValueOneOrigin() const { return mValue; }

        s32 addSelf(u32);
        s32 subSelf(u32);
        s32 sub(Month) const;

        static Month makeFromValueOneOrigin(u32 month);
        static SafeString makeStringOneOrigin(u32 month);

    private:
        s32 mValue;
    };

    enum class Week
    {
        Sunday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Max,
    };

    struct Time
    {
        Time(const Hour& h = cDefaultHour, const Minute& m = cDefaultMinute,
             const Second& s = cDefaultSecond);

        Hour mHour;
        Minute mMinute;
        Second mSecond;
    };

    struct Date
    {
        Date(const Year& y = cDefaultYear, const Month& month = cDefaultMonth,
             const Day& day = cDefaultDay);

        void calcWeek();

        Year mYear;
        Month mMonth;
        Day mDay;
        Week mWeek;
    };

    static const Month cMonth_Jan;
    static const Month cMonth_Feb;
    static const Month cMonth_Mar;
    static const Month cMonth_Apr;
    static const Month cMonth_May;
    static const Month cMonth_Jun;
    static const Month cMonth_Jul;
    static const Month cMonth_Aug;
    static const Month cMonth_Sep;
    static const Month cMonth_Oct;
    static const Month cMonth_Nov;
    static const Month cMonth_Dec;

    static const Year cDefaultYear;
    static const Month cDefaultMonth;
    static const Day cDefaultDay;
    static const Hour cDefaultHour;
    static const Minute cDefaultMinute;
    static const Second cDefaultSecond;

    CalendarTime(const Date& date, const Time& time);
    CalendarTime(const Year& year = cDefaultYear, const Month& month = cDefaultMonth,
                 const Day& day = cDefaultDay, const Hour& hour = cDefaultHour,
                 const Minute& minute = cDefaultMinute, const Second& second = cDefaultSecond);

    const Date& getDate() const { return mDate; }
    const Time& getTime() const { return mTime; }

    void setDate(const Date& date);
    void setTime(const Time& time) { mTime = time; }

    u32 getYearDays() const;
    u32 getYear() const { return mDate.mYear.getValue(); }
    const Month& getMonth() const { return mDate.mMonth; }
    u32 getDay() const { return mDate.mDay.getValue(); }
    Week getWeekDay() const { return mDate.mWeek; }
    u32 getHour() const { return mTime.mHour.getValue(); }
    u32 getMinute() const { return mTime.mMinute.getValue(); }
    u32 getSecond() const { return mTime.mSecond.getValue(); }

    void genHostIOMessage(hostio::Context*);
    void listenHostIOPropertyEvent(const hostio::PropertyEvent*, hostio::Reflexible*);

private:
    Date mDate;
    Time mTime;

    static void makeWeekDayNameLabel_(BufferedSafeString* out_span, Week week);
};

}  // namespace sead
