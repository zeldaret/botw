#pragma once

#include <basis/seadTypes.h>

namespace sead
{
/// A CalendarSpan represents a duration in terms of days, hours, minutes and seconds.
class CalendarSpan
{
public:
#define SEAD_CALENDARSPAN_MAKE_CLASS(NAME)                                                         \
    class NAME                                                                                     \
    {                                                                                              \
    public:                                                                                        \
        NAME(s32 v) : mValue(v) {}                                                                 \
        s32 getValue() const { return mValue; }                                                    \
        void setValue(s32 v) { mValue = v; }                                                       \
                                                                                                   \
    private:                                                                                       \
        s32 mValue;                                                                                \
    };

    SEAD_CALENDARSPAN_MAKE_CLASS(Day)
    SEAD_CALENDARSPAN_MAKE_CLASS(Hour)
    SEAD_CALENDARSPAN_MAKE_CLASS(Minute)
    SEAD_CALENDARSPAN_MAKE_CLASS(Second)
#undef SEAD_CALENDARSPAN_MAKE_CLASS

    CalendarSpan() : mDay(0), mHour(0), mMinute(0), mSecond(0) {}

    CalendarSpan(const Day& day, const Hour& hour, const Minute& minute, const Second& second)
        : mDay(day), mHour(hour), mMinute(minute), mSecond(second)
    {
    }

    s32 getDays() const { return mDay.getValue(); }
    s32 getHours() const { return mHour.getValue(); }
    s32 getMinutes() const { return mMinute.getValue(); }
    s32 getSeconds() const { return mSecond.getValue(); }

    void setDays(s32 days) { mDay.setValue(days); }
    void setHours(s32 hours) { mHour.setValue(hours); }
    void setMinutes(s32 minutes) { mMinute.setValue(minutes); }
    void setSeconds(s32 seconds) { mSecond.setValue(seconds); }

private:
    Day mDay;
    Hour mHour;
    Minute mMinute;
    Second mSecond;
};

}  // namespace sead
