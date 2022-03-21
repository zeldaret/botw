#include <time/seadDateSpan.h>
#include <time/seadDateUtil.h>

namespace sead
{
DateSpan::DateSpan(s64 span) : mSpan(span) {}

DateSpan::DateSpan(const CalendarSpan::Day& d, const CalendarSpan::Hour& h,
                   const CalendarSpan::Minute& m, const CalendarSpan::Second& s)
{
    set(d, h, m, s);
}

DateSpan::DateSpan(const CalendarSpan& span)
{
    set(span);
}

s64 DateSpan::set(const CalendarSpan& span)
{
    return setTimeImpl_(span.getDays(), span.getHours(), span.getMinutes(), span.getSeconds());
}

s64 DateSpan::set(const CalendarSpan::Day& d, const CalendarSpan::Hour& h,
                  const CalendarSpan::Minute& m, const CalendarSpan::Second& s)
{
    return setTimeImpl_(d.getValue(), h.getValue(), m.getValue(), s.getValue());
}

void DateSpan::getCalendarSpan(CalendarSpan* out_span) const
{
    DateUtil::calcSecondToCalendarSpan(out_span, mSpan);
}

s64 DateSpan::setTimeImpl_(s32 d, s32 h, s32 m, s32 s)
{
    mSpan = 86400ll * d + 3600ll * h + 60ll * m + s;
    return mSpan;
}

}  // namespace sead
