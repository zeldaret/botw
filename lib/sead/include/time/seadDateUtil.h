#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <time/seadCalendarTime.h>

namespace sead
{
class CalendarSpan;

namespace DateUtil
{
bool isLeapYear(u32 year);

CalendarTime::Week calcWeekDay(const CalendarTime::Year& year, const CalendarTime::Month& month,
                               const CalendarTime::Day& day);

void calcSecondToCalendarSpan(CalendarSpan* out_span, u64 seconds);

bool parseW3CDTFString(CalendarTime* out_time, CalendarSpan* out_span, const SafeString& string);
}  // namespace DateUtil
}  // namespace sead
