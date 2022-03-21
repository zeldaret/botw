#pragma once

#include <basis/seadTypes.h>
#include <time/seadCalendarSpan.h>

namespace sead
{
class DateSpan
{
public:
    explicit DateSpan(s64 span);
    DateSpan(const CalendarSpan::Day& d, const CalendarSpan::Hour& h, const CalendarSpan::Minute& m,
             const CalendarSpan::Second& s);
    DateSpan(const CalendarSpan& span);

    s64 set(const CalendarSpan& span);
    s64 set(const CalendarSpan::Day& d, const CalendarSpan::Hour& h, const CalendarSpan::Minute& m,
            const CalendarSpan::Second& s);

    s64 getSpan() const { return mSpan; }

    void getCalendarSpan(CalendarSpan* out_span) const;

    s64 getDays() const
    {
        CalendarSpan span;
        getCalendarSpan(&span);
        return span.getDays();
    }

    s64 getHours() const
    {
        CalendarSpan span;
        getCalendarSpan(&span);
        return span.getHours();
    }

    s64 getMinutes() const
    {
        CalendarSpan span;
        getCalendarSpan(&span);
        return span.getMinutes();
    }

    s64 getSeconds() const
    {
        CalendarSpan span;
        getCalendarSpan(&span);
        return span.getSeconds();
    }

    const DateSpan& operator+=(DateSpan other)
    {
        mSpan += other.mSpan;
        return *this;
    }

    const DateSpan& operator-=(DateSpan other)
    {
        mSpan -= other.mSpan;
        return *this;
    }

    const DateSpan& operator*=(f32 x)
    {
        mSpan *= x;
        return *this;
    }

    const DateSpan& operator/=(f32 x)
    {
        mSpan /= x;
        return *this;
    }

private:
    s64 setTimeImpl_(s32 d, s32 h, s32 m, s32 s);

    /// In seconds.
    s64 mSpan;
};
}  // namespace sead
