/**
 * @file time.h
 * @brief NEX Time Library.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace nex {
class TimeProvider;

class Time {
public:
    static void Reset();
    static void RegisterTimeProvider(TimeProvider* provider);

    Time Multiply(f32) const;
    Time Divide(f32) const;
    Time Scale(f32) const;

    static Time ConvertTimeoutToDeadline(u32 timeout);
    static u32 ConvertDeadlineToTimeout(Time deadline);

    u64 mCurTime;  // _0

    static u64* s_pfGetSessionTime;  // some sort of callback?
};

class SystemClock {
public:
    SystemClock();

    virtual ~SystemClock();

    static void RegisterTimeProvider(nn::nex::TimeProvider*, bool);
    static void ApplyCorrection(Time curTime, Time newTime);
    static Time ProtectedGetTime();
    static Time GetTimeImpl(bool);
    static Time GetTimeImplCorrectless();
    static void Reset();

    static nn::nex::TimeProvider* s_pTimeProvider;
    static bool s_needCorrection;
    static bool s_tiCorrection;
};
};  // namespace nex
};  // namespace nn