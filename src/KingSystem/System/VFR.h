#pragma once

#include <basis/seadTypes.h>
#include <cmath>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMathCalcCommon.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class VFR {
    SEAD_SINGLETON_DISPOSER(VFR)
    VFR();
    virtual ~VFR();

public:
    struct TimeSpeedMultiplier {
        TimeSpeedMultiplier();
        ~TimeSpeedMultiplier();
        TimeSpeedMultiplier(const TimeSpeedMultiplier&) = default;
        TimeSpeedMultiplier(TimeSpeedMultiplier&&) = default;
        TimeSpeedMultiplier& operator=(const TimeSpeedMultiplier&) = default;
        TimeSpeedMultiplier& operator=(TimeSpeedMultiplier&&) = default;

        void update(f32 multiplier);

        bool is_custom = false;
        f32 value = 1.0;
        f32 target_value = 1.0;
    };

    /// Changes the delta timing and restores the original value when going out of scope.
    struct ScopedDeltaSetter {
        ScopedDeltaSetter();
        ScopedDeltaSetter(u32 include_mask, u32 exclude_mask);
        ~ScopedDeltaSetter();
        ScopedDeltaSetter(const ScopedDeltaSetter&) = delete;
        ScopedDeltaSetter(ScopedDeltaSetter&&) = delete;
        auto operator=(const ScopedDeltaSetter&) = delete;
        auto operator=(ScopedDeltaSetter&&) = delete;
        void set(u32 include_mask, u32 exclude_mask);

        f32 mTimeRate = 1.0;
        f32 mPreviousDelta = 0.0;
    };

    void init(u32 interval, int num_speed_multipliers, sead::Heap* heap, u32 mask);

    void setIntervalOverride(u32 interval);
    void clearIntervalOverride();
    bool hasIntervalOverride() const;
    u32 getIntervalOverride() const;

    void updateInterval(u32 new_interval);

    void useBufferB();
    void useBufferA();

    f32 getDeltaAndSetMin(f32* raw_delta_frames, u32 include_mask, u32 exclude_mask);
    void resetTimeMultipliers();
    bool hasCustomTimeMultiplier() const;
    // TODO: requires ksys::Sound
    void setTimeMultiplier(u32 idx, f32 multiplier);
    // TODO: requires ksys::Sound
    void resetTimeMultiplier(u32 idx);

    f32 getDeltaTime(u32 core) const { return *mDeltaFrames[core]; }
    f32 getDeltaTime() const { return getDeltaTime(sead::CoreInfo::getCurrentCoreId()); }

    template <typename T>
    static inline void add(T* value, const T& v) {
        *value += v * instance()->getDeltaTime();
    }

    template <typename T>
    static inline void multiply(T* value, f32 scalar) {
        *value *= std::pow(scalar, instance()->getDeltaTime());
    }

    static inline f32 getLerpFactor(f32 t) {
        return 1.0f - std::pow(1.0f - t, instance()->getDeltaTime());
    }

    template <typename T>
    static inline void lerp(T* value, const T& b, f32 t) {
        *value += getLerpFactor(t) * (b - *value);
    }

    template <typename T>
    static inline void lerp(T* value, const T& b, f32 t, f32 max_delta) {
        const auto f = getLerpFactor(t);
        const auto max_d = instance()->getDeltaTime() * max_delta;
        const auto diff = b - *value;
        const auto d = f * sead::absf(diff);
        if (d > max_d)
            *value += diff < 0.0 ? -max_d : max_d;
        else
            *value += f * diff;
    }

    template <typename T>
    static inline bool lerp(T* value, const T& b, f32 t, f32 max_delta, f32 min_delta) {
        const auto f = getLerpFactor(t);
        const auto max_d = instance()->getDeltaTime() * max_delta;
        const auto min_d = instance()->getDeltaTime() * min_delta;

        const auto diff = b - *value;
        const auto d = f * sead::absf(diff);

        if (sead::absf(diff) <= min_d) {
            *value = b;
            return true;
        }

        if (d > max_d) {
            *value += diff < 0.0 ? -max_d : max_d;
        } else if (d < min_d) {
            *value += diff < 0.0 ? -min_d : min_d;
        } else {
            *value = *value + f * diff;
        }
        return false;
    }

private:
    struct TimeSpeedMultipliers : sead::Buffer<TimeSpeedMultiplier> {
        TimeSpeedMultipliers() {
            mBuffer = nullptr;
            mSize = 0;
        }
    };

    void setDelta(u32 core, f32 delta);
    void setDelta(f32 delta) { setDelta(sead::CoreInfo::getCurrentCoreId(), delta); }
    void setMinDelta(u32 core, const sead::BitFlag32& mask);
    void setMinDelta();
    void copyAtoB();

    bool mHasIntervalChanged = false;
    bool mHasIntervalOverride = false;
    u32 mIntervalOverride = 1;
    f32 mNewIntervalRatio = 1.0;
    u32 mIntervalA = 1;
    u32 mIntervalB = 1;
    f32 mIntervalRatioA = 1.0;
    f32 mIntervalRatioB = 1.0;

    static constexpr int NumCores = 3;

    sead::SafeArray<u32*, NumCores> mIntervals;
    sead::SafeArray<f32*, NumCores> mIntervalRatios;

    TimeSpeedMultipliers mTimeSpeedMultipliers;
    sead::BitFlag32 mMask = 0xffffffff;

    struct Storage {
        sead::SafeArray<f32, NumCores> raw_delta_frames{};
        sead::SafeArray<f32, NumCores> delta_frames{};
        sead::SafeArray<f32, NumCores> raw_delta_times{};
        sead::SafeArray<f32, NumCores> delta_times{};
    };
    sead::SafeArray<Storage, 2> mStorage{};

    /// Delta frames.
    sead::SafeArray<f32*, NumCores> mRawDeltaFrames;
    /// Delta frames, adjusted for present interval changes.
    sead::SafeArray<f32*, NumCores> mDeltaFrames;
    /// Delta times. Equals raw_delta_frame * frame_time.
    sead::SafeArray<f32*, NumCores> mRawDeltaTimes;
    /// Delta times, adjusted for present interval changes. Equals delta_frame * frame_time.
    sead::SafeArray<f32*, NumCores> mDeltaTimes;
    /// Present interval.
    u32 mInterval = 1;
    /// Frames per second.
    u32 mFrameRate = 60;
    /// Second per frame.
    f32 mFrameTime = 1.0 / 60.0;
};
KSYS_CHECK_SIZE_NX150(VFR, 0x160);

}  // namespace ksys
