#include "Game/UI/uiFadeProgress.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(FadeProgress)

void FadeProgress::init() {
    mActive = false;
    mProgress = 0.0;
    mGaugeValue = 0.0;
    mSteps = 1.0;
}

void FadeProgress::reset() {
    init();
}

void FadeProgress::updateFadeScreen() {
    if (!mActive)
        return;

    float progress = mProgress;
    float difference = progress - mGaugeValue;

    if (difference > 0.1f)
        mSteps = 1.1;
    if (difference > 0.2f)
        mSteps = 1.2;
    if (progress > 0.94f)
        mSteps = 10.0;

    if (difference <= 0.0001f && difference >= -0.0001f)
        mSteps = 1.0;

    float new_progress = mGaugeValue + (mProgressPerStep * mSteps);
    if (new_progress < progress)
        progress = new_progress;
    mGaugeValue = progress;
    applyScreenFade(progress);
}

void FadeProgress::setProgress(float value) {
    if (mProgress < value)
        mProgress = value;
}

float FadeProgress::getGaugeValue() const {
    return mGaugeValue;
}

void FadeProgress::setIsActive() {
    mActive = true;
}

}  // namespace uking::ui