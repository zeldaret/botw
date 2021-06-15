#include "KingSystem/System/VFRValue.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <prim/seadMemUtil.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys {

namespace {

util::InitTimeInfoEx sInitInfo;

template <typename T>
void updateStatsImpl(const T& value, T* prev_value, T* mean) {
    const T new_mean = ((*prev_value + value) / 2) * VFR::instance()->getDeltaTime();
    *prev_value = value;
    *mean = new_mean;
}

}  // namespace

VFRValue::VFRValue() = default;

VFRValue::VFRValue(const f32& value) : value{value}, prev_value{value}, mean{value} {}

void VFRValue::updateStats() {
    updateStatsImpl(value, &prev_value, &mean);
}

void VFRValue::operator+=(const f32& rhs) {
    VFR::add(&value, rhs);
}

void VFRValue::operator*=(f32 scalar) {
    VFR::multiply(&value, scalar);
}

void VFRValue::lerp(const f32& b, f32 t) {
    VFR::lerp(&value, b, t);
}

void VFRValue::lerp(const f32& b, f32 t, f32 max_delta) {
    VFR::lerp(&value, b, t, max_delta);
}

bool VFRValue::lerp(const f32& b, f32 t, f32 max_delta, f32 min_delta) {
    return VFR::lerp(&value, b, t, max_delta, min_delta);
}

bool VFRValue::chase(const f32& target, f32 step) {
    const auto delta = step * VFR::instance()->getDeltaTime();
    return sead::Mathf::chase(&value, target, delta);
}

VFRVec3f::VFRVec3f() : value{0, 0, 0}, prev_value{0, 0, 0}, mean{0, 0, 0} {}

VFRVec3f::VFRVec3f(const sead::Vector3f& value) : value{value}, prev_value{value}, mean{value} {}

// NON_MATCHING: float regalloc
void VFRVec3f::updateStats() {
    updateStatsImpl(value, &prev_value, &mean);
}

void VFRVec3f::operator*=(f32 scalar) {
    VFR::multiply(&value, scalar);
}

void VFRVec3f::lerp(const sead::Vector3f& b, f32 t) {
    VFR::lerp(&value, b, t);
}

bool VFRVec3f::chase(const sead::Vector3f& target, f32 t) {
    const auto delta = VFR::instance()->getDeltaTime() * t;
    const auto diff = target - value;
    const auto norm = sead::norm2(diff);

    if (norm <= delta) {
        sead::MemUtil::copy(&value, &target, sizeof(value));
        return true;
    }

    value += diff * (1.0f / norm) * delta;
    return false;
}

void VFRValue::setToMax(const f32& max) {
    const auto a = value;
    const auto b = max;
    value = a < b ? b : a;
}

void VFRValue::setToMin(const f32& min) {
    const auto a = value;
    const auto b = min;
    value = a > b ? b : a;
}

void VFRValue::clamp(const f32& min, const f32& max) {
    const auto a = min;
    const auto b = max;
    value = sead::clamp(value, a, b);
}

void VFRVec3f::normalize(f32 new_norm) {
    if (sead::norm2(value) > new_norm) {
        const auto norm = sead::norm2(value);
        if (norm > 0.0)
            value *= new_norm / norm;
    }
}

}  // namespace ksys
