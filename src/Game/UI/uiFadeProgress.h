#pragma once

#include <heap/seadDisposer.h>

namespace uking::ui {

class FadeProgress {
    SEAD_SINGLETON_DISPOSER(FadeProgress)
    FadeProgress() = default;
    ~FadeProgress() = default;

public:
    void init();
    void reset();
    void updateFadeScreen();
    void setProgress(float value);
    float getGaugeValue();
    void setIsActive();

private:
    bool mActive = false;
    f32 mProgress = 0.0;
    f32 mGaugeValue = 0.0;
    f32 mProgressPerStep = 0.002;
    f32 mSteps = 1.0;
};

}  // namespace uking::ui