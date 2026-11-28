#pragma once

#include "KingSystem/System/Timer.h"

namespace uking::ui {

struct DurationTimerBase {
    DurationTimerBase() {}

    ksys::Timer timer;
    f32 duration{0.0f};
};

struct DurationTimer : public DurationTimerBase {
    f32 direction{1.0f};
    bool is_zero_pending{false};

    void initSeconds(f32 seconds);
    void reset();
    void setSeconds(f32 seconds);
    void resetToEnd();
    bool isFinished() const;
    f32 getProgressRate() const;
    void update();
    void updateImpl();
    bool checkEnded();
    bool updateAndCheckEnded();
};

}  // namespace uking::ui