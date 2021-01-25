#include "KingSystem/System/VFR.h"
#include <mc/seadCoreInfo.h>

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(VFR)

VFR::VFR() {
    for (int i = 0; i < NumCores; ++i) {
        mRawDeltaFrames[i] = &mStorage[0].raw_delta_frames[i];
        mDeltaFrames[i] = &mStorage[0].delta_frames[i];
        mRawDeltaTimes[i] = &mStorage[0].raw_delta_times[i];
        mDeltaTimes[i] = &mStorage[0].delta_times[i];
        mIntervals[i] = &mIntervalA;
        mIntervalRatios[i] = &mIntervalRatioA;
    }
}

VFR::~VFR() {
    mTimeSpeedMultipliers.freeBuffer();
}

void VFR::setDelta(u32 core, f32 delta) {
    delta = sead::Mathf::max(delta, 0.01f);
    *mRawDeltaFrames[core] = delta;
    *mDeltaFrames[core] = delta * *mIntervalRatios[core];
    *mRawDeltaTimes[core] = delta * mFrameTime;
    *mDeltaTimes[core] = *mDeltaFrames[core] * mFrameTime;
}

void VFR::setMinDelta(u32 core, const sead::BitFlag32& mask) {
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
    setMinDelta();
}

void VFR::setMinDelta() {
    setMinDelta(0, mMask);

    for (s32 i = 0; i < NumCores; ++i) {
        mStorage[0].delta_frames[i] = mStorage[0].delta_frames[0];
        mStorage[0].raw_delta_times[i] = mStorage[0].raw_delta_times[0];
        mStorage[0].delta_times[i] = mStorage[0].delta_times[0];
        mStorage[0].raw_delta_frames[i] = mStorage[0].raw_delta_frames[0];
    }
}

void VFR::copyAtoB() {
    for (s32 i = 0; i < NumCores; ++i) {
        mStorage[1].raw_delta_frames[i] = mStorage[0].raw_delta_frames[i];
        mStorage[1].delta_frames[i] = mStorage[0].delta_frames[i];
        mStorage[1].raw_delta_times[i] = mStorage[0].raw_delta_times[i];
        mStorage[1].delta_times[i] = mStorage[0].delta_times[i];
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
    setMinDelta();
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

    setMinDelta();
}

void VFR::useBufferB() {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    mRawDeltaFrames[core] = &mStorage[1].raw_delta_frames[core];
    mDeltaFrames[core] = &mStorage[1].delta_frames[core];
    mRawDeltaTimes[core] = &mStorage[1].raw_delta_times[core];
    mDeltaTimes[core] = &mStorage[1].delta_times[core];
    mIntervals[core] = &mIntervalB;
    mIntervalRatios[core] = &mIntervalRatioB;
}

void VFR::useBufferA() {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    mRawDeltaFrames[core] = &mStorage[0].raw_delta_frames[core];
    mDeltaFrames[core] = &mStorage[0].delta_frames[core];
    mRawDeltaTimes[core] = &mStorage[0].raw_delta_times[core];
    mDeltaTimes[core] = &mStorage[0].delta_times[core];
    mIntervals[core] = &mIntervalA;
    mIntervalRatios[core] = &mIntervalRatioA;
}

f32 VFR::getDeltaAndSetMin(f32* raw_delta_frames, u32 include_mask, u32 exclude_mask) {
    const u32 core = sead::CoreInfo::getCurrentCoreId();
    *raw_delta_frames = *mRawDeltaFrames[core];
    const f32 delta = *mDeltaFrames[core];
    setMinDelta(core, (mMask.getDirect() | include_mask) & ~exclude_mask);
    return delta;
}

bool VFR::hasCustomTimeMultiplier() const {
    for (const auto& entry : mTimeSpeedMultipliers) {
        if (entry.value != 1.0)
            return true;
    }
    return false;
}

VFR::ScopedDeltaSetter::ScopedDeltaSetter() = default;

VFR::ScopedDeltaSetter::ScopedDeltaSetter(u32 include_mask, u32 exclude_mask)
    : ScopedDeltaSetter() {
    set(include_mask, exclude_mask);
}

void VFR::ScopedDeltaSetter::set(u32 include_mask, u32 exclude_mask) {
    auto* vfr = VFR::instance();
    if (!vfr)
        return;

    f32 raw_delta;
    const auto delta = vfr->getDeltaAndSetMin(&raw_delta, include_mask, exclude_mask);
    const auto time = vfr->getDeltaTime();
    if (delta != time) {
        mPreviousDelta = raw_delta;
        if (delta > 0.0)
            mTimeRate = time / delta;
    }
}

VFR::ScopedDeltaSetter::~ScopedDeltaSetter() {
    if (VFR::instance() && mPreviousDelta > 0.0)
        VFR::instance()->setDelta(mPreviousDelta);
}

}  // namespace ksys
