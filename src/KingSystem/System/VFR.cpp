#include "KingSystem/System/VFR.h"
#include <mc/seadCoreInfo.h>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(VFR)

VFR::VFR() {
    for (int i = 0; i < NumCores; ++i) {
        mPtrs1[i] = &mFloats1a[i];
        mDeltaTimes[i] = &mFloats2a[i];
        mPtrs3[i] = &mFloats3a[i];
        mDeltaFrames[i] = &mFloats4a[i];
        mIntervals[i] = &mIntervalA;
        mIntervalRatios[i] = &mIntervalRatioA;
    }
}

VFR::~VFR() {
    mTimeSpeedMultipliers.freeBuffer();
}

void VFR::setDelta(u32 core, f32 delta) {
    delta = sead::Mathf::max(delta, 0.01f);
    *mPtrs1[core] = delta;
    *mDeltaTimes[core] = delta * *mIntervalRatios[core];
    *mPtrs3[core] = delta * mFrameTime;
    *mDeltaFrames[core] = *mDeltaTimes[core] * mFrameTime;
}

void VFR::setDeltaFromTimeMultipliers(u32 core, const sead::BitFlag32& mask) {
    f32 min = 1.0;
    for (s32 i = 0; i < mTimeSpeedMultipliers.size(); ++i) {
        if (mask.isOnBit(i))
            min = sead::Mathf::min(min, mTimeSpeedMultipliers[i].value);
    }
    setDelta(core, min);
}

void VFR::resetTimeMultipliers() {
    for (auto& entry : mTimeSpeedMultipliers) {
        entry.value = 1.0;
        entry.target_value = 1.0;
        entry.is_custom = false;
    }
    x_1();
}

void VFR::x_1() {
    setDeltaFromTimeMultipliers(0, mMask);

    for (s32 i = 0; i < NumCores; ++i) {
        mFloats2a[i] = mFloats2a[0];
        mFloats3a[i] = mFloats3a[0];
        mFloats4a[i] = mFloats4a[0];
        mFloats1a[i] = mFloats1a[0];
    }
}

void VFR::copyAtoB() {
    for (s32 i = 0; i < NumCores; ++i) {
        mFloats1b[i] = mFloats1a[i];
        mFloats2b[i] = mFloats2a[i];
        mFloats3b[i] = mFloats3a[i];
        mFloats4b[i] = mFloats4a[i];
        mIntervalB = mIntervalA;
        mIntervalRatioB = mIntervalRatioA;
    }
}

void VFR::init(u32 interval, int num_speed_multipliers, sead::Heap* heap, u32 mask) {
    mInterval = interval;
    mFrameRate = 60 / interval;
    mIntervalA = interval;
    mIntervalB = interval;
    mFrameTime = 1.0f / mFrameRate;
    mTimeSpeedMultipliers.allocBufferAssert(num_speed_multipliers, heap);
    mMask = mask;
    x_1();
    copyAtoB();
}

void VFR::setIntervalOverride(u32 interval) {
    if (!mHasIntervalOverride) {
        mHasIntervalOverride = true;
        mIntervalOverride = interval;
    }
}

void VFR::clearIntervalOverride() {
    mHasIntervalOverride = false;
}

bool VFR::hasIntervalOverride() const {
    return mHasIntervalOverride;
}

u32 VFR::getIntervalOverride() const {
    return mIntervalOverride;
}

VFR::TimeSpeedMultiplier::TimeSpeedMultiplier() = default;

VFR::TimeSpeedMultiplier::~TimeSpeedMultiplier() = default;

void VFR::TimeSpeedMultiplier::update(f32 multiplier) {
    if (target_value == value)
        return;

    is_custom = target_value != 1.0;
    if (target_value < value) {
        value = target_value;
    } else {
        sead::Mathf::chase(&value, target_value, sead::Mathf::max(value * multiplier, 0.01));
    }
}

void VFR::updateInterval(u32 new_interval) {
    copyAtoB();

    if (mHasIntervalOverride)
        new_interval = mIntervalOverride;

    if (new_interval != 0 && mIntervalA != new_interval) {
        mIntervalA = new_interval;
        mHasIntervalChanged = true;
        mNewIntervalRatio = f32(new_interval) * (1.0f / mInterval);
    } else {
        mHasIntervalChanged = false;
    }

    if (mNewIntervalRatio != mIntervalRatioA)
        mIntervalRatioA = mNewIntervalRatio;

    for (s32 i = 0; i < mTimeSpeedMultipliers.size(); ++i) {
        mTimeSpeedMultipliers[i].update(mIntervalRatioA);
    }

    x_1();
}

void VFR::useBufferB() {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    mPtrs1[core] = &mFloats1b[core];
    mDeltaTimes[core] = &mFloats2b[core];
    mPtrs3[core] = &mFloats3b[core];
    mDeltaFrames[core] = &mFloats4b[core];
    mIntervals[core] = &mIntervalB;
    mIntervalRatios[core] = &mIntervalRatioB;
}

void VFR::useBufferA() {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    mPtrs1[core] = &mFloats1a[core];
    mDeltaTimes[core] = &mFloats2a[core];
    mPtrs3[core] = &mFloats3a[core];
    mDeltaFrames[core] = &mFloats4a[core];
    mIntervals[core] = &mIntervalA;
    mIntervalRatios[core] = &mIntervalRatioA;
}

f32 VFR::setDeltaFromTimeMultipliers(f32* value, u32 include_mask, u32 exclude_mask) {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    *value = *mPtrs1[core];
    const f32 delta = *mDeltaTimes[core];
    setDeltaFromTimeMultipliers(core, (mMask.getDirect() | include_mask) & ~exclude_mask);
    return delta;
}

bool VFR::hasCustomTimeMultiplier() const {
    for (const auto& entry : mTimeSpeedMultipliers) {
        if (entry.value != 1.0)
            return true;
    }
    return false;
}

VFR::Stopwatch::Stopwatch() = default;

VFR::Stopwatch::Stopwatch(u32 include_mask, u32 exclude_mask) : Stopwatch() {
    start(include_mask, exclude_mask);
}

void VFR::Stopwatch::start(u32 include_mask, u32 exclude_mask) {
    auto* vfr = VFR::instance();
    if (!vfr)
        return;

    f32 duration;
    const auto delta = vfr->setDeltaFromTimeMultipliers(&duration, include_mask, exclude_mask);
    const auto time = vfr->getDeltaTime();
    if (delta != time) {
        mTimeDelta = duration;
        if (delta > 0.0)
            mTimeRate = time / delta;
    }
}

VFR::Stopwatch::~Stopwatch() {
    if (VFR::instance() && mTimeDelta > 0.0)
        VFR::instance()->setDelta(mTimeDelta);
}

}  // namespace ksys
