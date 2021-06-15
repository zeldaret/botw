#include "KingSystem/GameData/gdtFlag.h"

namespace ksys::gdt {

FlagProperties::FlagProperties() = default;

FlagProperties::~FlagProperties() = default;

void FlagProperties::setIsProgramReadable(bool on) {
    set(PropertyFlag::IsProgramReadable, on);
}

bool FlagProperties::isProgramReadable() const {
    return get(PropertyFlag::IsProgramReadable);
}

void FlagProperties::setIsProgramWritable(bool on) {
    set(PropertyFlag::IsProgramWritable, on);
}

bool FlagProperties::isProgramWritable() const {
    return get(PropertyFlag::IsProgramWritable);
}

void FlagProperties::setIsSave(bool on) {
    set(PropertyFlag::IsSave, on);
}

bool FlagProperties::isSave() const {
    return get(PropertyFlag::IsSave);
}

void FlagProperties::setIsOneTrigger(bool on) {
    set(PropertyFlag::IsOneTrigger, on);
}

bool FlagProperties::isOneTrigger() const {
    return get(PropertyFlag::IsOneTrigger);
}

void FlagProperties::setIsEventAssociated(bool on) {
    set(PropertyFlag::IsEventAssociated, on);
}

bool FlagProperties::isEventAssociated() const {
    return get(PropertyFlag::IsEventAssociated);
}

void FlagProperties::setResetType(ResetType type) {
    mFlags = (mFlags & 0x1F) | 0x20 * u32(type);
}

ResetType FlagProperties::getResetType() const {
    return ResetType(mFlags >> 5);
}

FlagProperties& FlagProperties::operator=(const FlagProperties& other) {
    setIsProgramReadable(other.isProgramReadable());
    setIsProgramWritable(other.isProgramWritable());
    setIsSave(other.isSave());
    setIsOneTrigger(other.isOneTrigger());
    setIsEventAssociated(other.isEventAssociated());
    setResetType(other.getResetType());
    return *this;
}

s32 FlagBase::clampValue_(const s32& min_value, s32* value, const s32& max_value) {
    if (*value < min_value) {
        *value = min_value;
        return -1;
    }
    if (*value > max_value) {
        *value = max_value;
        return 1;
    }
    return 0;
}

s32 FlagBase::clampValue_(const f32& min_value, f32* value, const f32& max_value) {
    if (*value < min_value) {
        *value = min_value;
        return -1;
    }
    if (*value > max_value) {
        *value = max_value;
        return 1;
    }
    return 0;
}

s32 FlagBase::clampValue_(const sead::SafeString&, sead::SafeString*, const sead::SafeString&) {
    return 0;
}

namespace {
template <typename T>
constexpr s32 clampVectorComponentWise(const T& min_value, T* value, const T& max_value) {
    s32 ret = 0;
    for (size_t i = 0; i < min_value.e.size(); ++i) {
        if (value->e[i] < min_value.e[i]) {
            value->e[i] = min_value.e[i];
            ret = -1;
        }
    }
    for (size_t i = 0; i < max_value.e.size(); ++i) {
        if (value->e[i] > max_value.e[i]) {
            value->e[i] = max_value.e[i];
            ret = 1;
        }
    }
    return ret;
}
}  // namespace

s32 FlagBase::clampValue_(const sead::Vector2f& min_value, sead::Vector2f* value,
                          const sead::Vector2f& max_value) {
    return clampVectorComponentWise(min_value, value, max_value);
}

s32 FlagBase::clampValue_(const sead::Vector3f& min_value, sead::Vector3f* value,
                          const sead::Vector3f& max_value) {
    return clampVectorComponentWise(min_value, value, max_value);
}

s32 FlagBase::clampValue_(const sead::Vector4f& min_value, sead::Vector4f* value,
                          const sead::Vector4f& max_value) {
    return clampVectorComponentWise(min_value, value, max_value);
}

bool FlagBase::isBoolean_() const {
    const auto type = getType();
    return s32(type) == FlagType::Bool || s32(type) == FlagType::BoolArray;
}

u32 FlagBase::getCategoryForBool_(const void* data) const {
    if (!isBoolean_())
        return 0;
    return *static_cast<const u8*>(data) >> 1;
}

void FlagBase::setCategoryForBool_(void* data, u32 category) const {
    if (!isBoolean_())
        return;

    auto* ptr = static_cast<u8*>(data);
    *ptr = (*ptr & 1) | 2 * category;
}

}  // namespace ksys::gdt
