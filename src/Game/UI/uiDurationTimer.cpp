#include "uiDurationTimer.h"

#include "KingSystem/System/VFR.h"
#include "math/seadMathCalcCommon.h"

namespace uking::ui {

void DurationTimer::initSeconds(f32 seconds) {
    setSeconds(seconds);

    // TODO: may wanna call ksys::Timer::reset, or just init that base class
    rate = 1.0f;
    value = 0.0f;
    previous_value = 0.0f;

    is_zero_pending = seconds == 0.0f;
}

void DurationTimer::reset() {
    value = 0.0f;
    previous_value = 0.0f;
    rate = 1.0f;
}

void DurationTimer::setSeconds(f32 seconds) {
    duration = seconds * 30.0f;
}

void DurationTimer::resetToEnd() {
    previous_value = value = duration;
    rate = 1.0f;
}

bool DurationTimer::isFinished() const {
    if (direction > 0.0f)
        return duration <= value;
    if (direction < 0.0f)
        return value < 0.0f;
    return true;
}

f32 DurationTimer::getProgressRate() const {
    return duration == 0.0f ? 1.0f : sead::Mathf::clamp(value / duration, 0.0f, 1.0f);
}

void DurationTimer::update() {
    updateImpl();
}

void DurationTimer::updateImpl() {
    if (!hasEnded(duration) && isFinished())
        return;

    if (ksys::VFR::instance()) {
        ksys::VFR::ScopedDeltaSetter setter(0, 1);
        ksys::Timer::update();
    } else {
        rate = 1.0f;
        ksys::Timer::update();
    }
}

bool DurationTimer::checkEnded() {
    if (duration == 0.0f) {
        if (!is_zero_pending)
            return false;
        is_zero_pending = false;
        return true;
    }
    return hasEnded(duration);
}

bool DurationTimer::updateAndCheckEnded() {
    if (duration == 0.0f) {
        if (is_zero_pending) {
            is_zero_pending = false;
            return true;
        }
        return false;
    }
    update();
    return hasEnded(duration);
}

}  // namespace uking::ui