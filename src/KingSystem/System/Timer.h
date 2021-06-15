#pragma once

#include <basis/seadTypes.h>

namespace ksys {

struct Timer {
    Timer() = default;
    Timer(f32 value, f32 previous_value, f32 rate = -1.0)
        : value(value), previous_value(previous_value), rate(rate) {}

    void reset(f32 value_, f32 rate_ = -1.0) {
        value = previous_value = value_;
        rate = rate_;
    }

    void update();
    static void update(f32* t, f32 rate);
    bool hasEnded(f32 end_time) const;

    f32 value{};
    f32 previous_value{};
    f32 rate{};
};

}  // namespace ksys
