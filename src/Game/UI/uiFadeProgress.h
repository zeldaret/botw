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
    float getGaugeValue() const;
    void setIsActive();

private:
    bool mActive = false;
    float mProgress = 0.0;
    float mGaugeValue = 0.0;
    float mProgressPerStep = 0.002;
    float mSteps = 1.0;
};

}  // namespace uking::ui
