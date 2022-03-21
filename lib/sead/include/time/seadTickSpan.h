#ifndef SEAD_TICKSPAN_H_
#define SEAD_TICKSPAN_H_

#include <climits>

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>

namespace sead
{
/// A TickSpan represents a number of ticks.
class TickSpan
{
public:
    TickSpan(s64 span = 0) : mSpan(span) {}

    s64 toS64() const { return mSpan; }
    s64 toTicks() const { return mSpan; }

    s64 toNanoSeconds() const;

    s64 toMicroSeconds() const { return toNanoSeconds() / 1000; }

    s64 toMilliSeconds() const
    {
        if (u64(mSpan) + (LLONG_MAX / 1000) < u64(ULLONG_MAX / 1000) - 1)
            return 1000 * mSpan / cFrequency;
        return 1000 * (mSpan / cFrequency);
    }

    s64 toSeconds() const { return toMilliSeconds() / 1000; }

    void setNanoSeconds(s64 nsec);

    void setMicroSeconds(s64 usec)
    {
        SEAD_ASSERT(LLONG_MIN / cFrequency <= usec && usec < LLONG_MAX / cFrequency);
        mSpan = usec * cFrequency / 1000 / 1000;
    }

    void setMilliSeconds(s64 msec)
    {
        SEAD_ASSERT(LLONG_MIN / cFrequency <= msec && msec < LLONG_MAX / cFrequency);
        mSpan = msec * cFrequency / 1000;
    }

    void setSeconds(s64 sec)
    {
        SEAD_ASSERT(LLONG_MIN / cFrequency <= sec && sec < LLONG_MAX / cFrequency);
        mSpan = sec * cFrequency;
    }

    const TickSpan& operator+=(TickSpan span)
    {
        mSpan += span.mSpan;
        return *this;
    }

    const TickSpan& operator-=(TickSpan span)
    {
        mSpan -= span.mSpan;
        return *this;
    }

    const TickSpan& operator*=(f32 x)
    {
        mSpan *= x;
        return *this;
    }

    const TickSpan& operator/=(f32 x)
    {
        mSpan /= x;
        return *this;
    }

    friend TickSpan operator+(TickSpan a, TickSpan b) { return a.mSpan + b.mSpan; }
    friend TickSpan operator-(TickSpan a, TickSpan b) { return a.mSpan - b.mSpan; }
    friend TickSpan operator*(TickSpan a, f32 x) { return a.mSpan * x; }
    friend TickSpan operator*(f32 x, TickSpan a) { return a.mSpan * x; }
    friend TickSpan operator/(TickSpan a, f32 x) { return a.mSpan / x; }

    static TickSpan makeFromNanoSeconds(s64 nsec)
    {
        TickSpan span;
        span.setNanoSeconds(nsec);
        return span;
    }

    static TickSpan makeFromMicroSeconds(s64 usec)
    {
        TickSpan span;
        span.setMicroSeconds(usec);
        return span;
    }

    static TickSpan makeFromMilliSeconds(s64 msec)
    {
        TickSpan span;
        span.setMilliSeconds(msec);
        return span;
    }

    static TickSpan makeFromSeconds(s64 sec)
    {
        TickSpan span;
        span.setSeconds(sec);
        return span;
    }

private:
    s64 mSpan;

    /// Number of ticks per second. This is platform specific.
    static const s64 cFrequency;
};

}  // namespace sead

#endif  // SEAD_TICKSPAN_H_
