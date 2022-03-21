#include <prim/seadStringUtil.h>
#include <time/seadCalendarSpan.h>
#include <time/seadDateUtil.h>

namespace sead
{
namespace DateUtil
{
bool isLeapYear(u32 year)
{
#ifdef MATCHING_HACK_NX_CLANG
    bool div100, div4;
    return (div100 = year % 100 == 0, div4 = year % 4 == 0, !div100 & div4) | (year % 400 == 0);
#else
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
#endif
}

CalendarTime::Week calcWeekDay(const CalendarTime::Year& year, const CalendarTime::Month& month,
                               const CalendarTime::Day& day)
{
    int y = year.getValue();
    int m = month.getValueOneOrigin();
    int d = day.getValue();
    if (m < 3)
    {
        y -= 1;
        m += 12;
    }
    d += y + (y / 4) - (y / 100) + (y / 400);
    d += (26 * m + 16) / 10;
    return CalendarTime::Week(d % 7);
}

void calcSecondToCalendarSpan(CalendarSpan* out_span, u64 sec)
{
    if (!out_span)
        return;
    out_span->setDays(sec / (3600 * 24));
    out_span->setHours((sec % (3600 * 24)) / 3600);
    out_span->setMinutes((sec % 3600) / 60);
    out_span->setSeconds(sec % 60);
}

bool parseW3CDTFSubString(bool* ok, u32* value, SafeString* str, s32* str_length,
                          char* out_separator, s32 parse_length, const SafeString& separators,
                          bool allow_null_separator, u32 value_min, u32 value_max)
{
    if (*str_length < parse_length)
    {
        *ok = false;
        return true;
    }

    const char c = str->at(parse_length);
    if (!separators.include(c) && (!allow_null_separator || c != SafeString::cNullChar))
    {
        *ok = false;
        return true;
    }

    FixedSafeString<8> buffer;
    buffer.copy(*str, parse_length);

    if (!StringUtil::tryParseU32(value, buffer, StringUtil::CardinalNumber::Base10) ||
        *value < value_min || *value > value_max)
    {
        *ok = false;
        return true;
    }

    if (c == SafeString::cNullChar)
    {
        *ok = true;
        return true;
    }

    *str = str->getPart(parse_length + 1);
    *str_length -= parse_length + 1;
    if (out_separator)
        *out_separator = c;
    return false;
}

static bool parseW3CDTFStringImpl(u32* year, u32* month, u32* day, u32* hour, u32* minute,
                                  u32* second, s32* tz_hour, s32* tz_minute,
                                  const SafeString& string)
{
    s32 len = string.calcLength();
    bool ok = true;
    SafeString substr = string;
    char separator;

    if (parseW3CDTFSubString(&ok, year, &substr, &len, &separator, 4, "-", true, 0, 0xFFFFFFFF))
        return ok;
    if (parseW3CDTFSubString(&ok, month, &substr, &len, &separator, 2, "-", true, 1, 12))
        return ok;
    if (parseW3CDTFSubString(&ok, day, &substr, &len, &separator, 2, "T", true, 1, 31))
        return ok;
    if (parseW3CDTFSubString(&ok, hour, &substr, &len, &separator, 2, ":", false, 0, 23))
        return ok;
    if (parseW3CDTFSubString(&ok, minute, &substr, &len, &separator, 2, ":+-Z", true, 0, 59))
        return ok;

    if (separator == ':')
    {
        if (parseW3CDTFSubString(&ok, second, &substr, &len, &separator, 2, ".+-Z", true, 0, 59))
            return ok;

        if (separator == '.')
        {
            if (len == 0)
                return false;

            auto it = substr.tokenBegin("+-Z");
            ++it;
            auto end = substr.tokenEnd("+-Z");

            // No timezone information
            if (it == end)
            {
                *tz_hour = 0;
                *tz_minute = 0;
                return true;
            }

            separator = substr.at(it.getIndex() - 1);
            substr = substr.getPart(it.getIndex());
            len -= it.getIndex();
        }
    }

    if (separator != '+' && separator != '-')
    checkLength:
        return len == 0;

    bool done;
    u32 tz_hour_abs = 0;
    done = parseW3CDTFSubString(&ok, &tz_hour_abs, &substr, &len, nullptr, 2, ":", false, 0, 11);
    if (ok)
    {
        *tz_hour = tz_hour_abs;
        if (separator == '-')
            *tz_hour = -tz_hour_abs;
    }
    if (done)
        return ok;

    u32 tz_minute_abs = 0;
    done = parseW3CDTFSubString(&ok, &tz_minute_abs, &substr, &len, nullptr, 2, "", true, 0, 59);
    if (ok)
    {
        *tz_minute = tz_minute_abs;
        if (separator == '-')
            *tz_minute = -tz_minute_abs;

        if (done)
        {
            len -= 2;
            goto checkLength;
        }
    }

    return false;
}

bool parseW3CDTFString(CalendarTime* out_time, CalendarSpan* time_zone, const SafeString& string)
{
    u32 year = 1970;
    u32 month = 1;
    u32 day = 1;
    u32 hour = 0;
    u32 minute = 0;
    u32 second = 0;

    s32 tz_hour = 0;
    s32 tz_minute = 0;

    const bool ret = parseW3CDTFStringImpl(&year, &month, &day, &hour, &minute, &second, &tz_hour,
                                           &tz_minute, string);

    if (ret)
    {
        out_time->setDate({year, CalendarTime::Month::makeFromValueOneOrigin(month), day});
        out_time->setTime({hour, minute, second});

        time_zone->setDays(0);
        time_zone->setHours(tz_hour);
        time_zone->setMinutes(tz_minute);
        time_zone->setSeconds(0);
    }

    return ret;
}
}  // namespace DateUtil
}  // namespace sead
