#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFR.h"

namespace ksys {

void Timer::update(f32* t, f32 rate) {
    *t += VFR::instance()->getDeltaTime() * rate;
}

void Timer::update() {
    previous_value = value;
    update(&value, rate);
}

bool Timer::hasEnded(f32 end_time) const {
    if (value == end_time)
        return true;

    return (previous_value - end_time) * (value - end_time) < 0.0;
}

}  // namespace ksys
