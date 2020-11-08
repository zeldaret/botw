#pragma once

#include <basis/seadTypes.h>

namespace ksys {

struct Timer {
    Timer() = default;
    Timer(f32 value, f32 previous_value, f32 speed = -1.0)
        : value(value), previous_value(previous_value), speed(speed) {}

    void reset(f32 value_, f32 speed_ = -1.0) {
        value = previous_value = value_;
        speed = speed_;
    }

    void update();
    static void update(f32& t);
    bool hasEnded(f32 end_time) const;

    f32 value{};
    f32 previous_value{};
    f32 speed{};
};

}  // namespace ksys
