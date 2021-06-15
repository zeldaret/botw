#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys {

/// A time-scaled floating-point value.
struct VFRValue {
    VFRValue();
    explicit VFRValue(const f32& value);

    void updateStats();
    void operator+=(const f32& rhs);
    void operator*=(f32 scalar);
    void lerp(const f32& b, f32 t);
    void lerp(const f32& b, f32 t, f32 max_delta);
    bool lerp(const f32& b, f32 t, f32 max_delta, f32 min_delta);
    bool chase(const f32& target, f32 step);
    void setToMax(const f32& max);
    void setToMin(const f32& min);
    void clamp(const f32& min, const f32& max);

    f32 value{};
    f32 prev_value{};
    f32 mean{};
};

/// A time-scaled Vector3f.
struct VFRVec3f {
    VFRVec3f();
    explicit VFRVec3f(const sead::Vector3f& value);

    void updateStats();
    void operator*=(f32 scalar);
    void lerp(const sead::Vector3f& b, f32 t);
    bool chase(const sead::Vector3f& target, f32 t);
    /// Normalize the `value` vector if its norm is greater than `new_norm`.
    /// Normalization will make the norm equal to `new_norm`.
    void normalize(f32 new_norm);

    sead::Vector3f value;
    sead::Vector3f prev_value;
    sead::Vector3f mean;
};

}  // namespace ksys
