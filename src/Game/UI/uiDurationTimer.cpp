#include "uiDurationTimer.h"

#include "KingSystem/System/VFR.h"
#include "math/seadMathCalcCommon.h"

namespace uking::ui {

void DurationTimer::initSeconds(f32 seconds) {
    duration = seconds * 30.0f;
    timer.reset(0.0f, 1.0f);
    is_zero_pending = seconds == 0.0f;
}

void DurationTimer::reset() {
    timer.reset(0.0f, 1.0f);
}

void DurationTimer::setSeconds(f32 seconds) {
    duration = seconds * 30.0f;
}

void DurationTimer::resetToEnd() {
    timer.reset(duration, 1.0f);
}

bool DurationTimer::isFinished() const {
    if (direction > 0.0f)
        return duration <= timer.value;
    if (direction < 0.0f)
        return timer.value < 0.0f;
    return true;
}

f32 DurationTimer::getProgressRate() const {
    return duration == 0.0f ? 1.0f : sead::Mathf::clamp(timer.value / duration, 0.0f, 1.0f);
}

void DurationTimer::update() {
    updateImpl();
}

void DurationTimer::updateImpl() {
    if (!timer.hasEnded(duration) && isFinished())
        return;

    if (ksys::VFR::instance()) {
        ksys::VFR::ScopedDeltaSetter setter(0, 1);
        timer.update();
    } else {
        timer.rate = 1.0f;
        timer.update();
    }
}

bool DurationTimer::checkEnded() {
    if (duration == 0.0f) {
        if (!is_zero_pending)
            return false;
        is_zero_pending = false;
        return true;
    }
    return timer.hasEnded(duration);
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
    return timer.hasEnded(duration);
}

}  // namespace uking::ui