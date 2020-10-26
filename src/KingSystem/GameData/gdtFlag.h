#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <prim/seadSizedEnum.h>
#include <type_traits>
#include "KingSystem/Utils/TypeTraits.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::gdt {

enum class ResetType {
    /// The flag will not be reset.
    NoReset = 0,
    /// The flag is reset every time a blood moon occurs.
    ResetOnBloodMoon = 1,
    /// The flag is reset every time a stage is generated.
    ResetOnStageGeneration = 2,
    /// The flag is reset every day at midnight.
    ResetAtMidnight = 3,
    /// The flag is reset every time the Lord of the Mountain makes an appearance.
    ResetOnAnimalMasterAppearance = 4,
};

constexpr bool isResettableFlag(ResetType type) {
    return type > ResetType::NoReset;
}

struct FlagDebugData {
    sead::SafeString name;
    s32 delete_rev = 0;
    u32 _14 = 0;
};
KSYS_CHECK_SIZE_NX150(FlagDebugData, 0x18);

class FlagProperties {
public:
    FlagProperties();
    FlagProperties(const FlagProperties& other) { *this = other; }
    ~FlagProperties();
    FlagProperties& operator=(const FlagProperties& other);

    void setIsProgramReadable(bool on);
    bool isProgramReadable() const;

    void setIsProgramWritable(bool on);
    bool isProgramWritable() const;

    void setIsSave(bool on);
    bool isSave() const;

    void setIsOneTrigger(bool on);
    bool isOneTrigger() const;

    void setIsEventAssociated(bool on);
    bool isEventAssociated() const;

    void setResetType(ResetType type);
    ResetType getResetType() const;

private:
    enum class PropertyFlag {
        IsProgramReadable = 0x1,
        IsProgramWritable = 0x2,
        IsSave = 0x4,
        IsOneTrigger = 0x8,
        IsEventAssociated = 0x10,
    };

    void set(PropertyFlag flag, bool on) {
        if (on)
            mFlags |= u8(flag);
        else
            mFlags &= ~u8(flag);
    }

    bool get(PropertyFlag flag) const { return (mFlags & u8(flag)) != 0; }

    u8 mFlags{};
};
KSYS_CHECK_SIZE_NX150(FlagProperties, 0x1);

SEAD_ENUM(FlagType, Bool = 0, S32 = 1, F32 = 2, String = 3, String64 = 4, String256 = 5,
          Vector2f = 6, Vector3f = 7, Vector4f = 8, BoolArray = 9, S32Array = 10, F32Array = 11,
          StringArray = 12, String64Array = 13, String256Array = 14, Vector2fArray = 15,
          Vector3fArray = 16, Vector4fArray = 17, Invalid = 18)

template <typename T>
constexpr bool isValidFlagArrayType() {
    return IsAnyOfType<T, sead::Buffer<bool>, sead::Buffer<s32>, sead::Buffer<f32>,
                       sead::Buffer<sead::FixedSafeString<32>>,
                       sead::Buffer<sead::FixedSafeString<64>>,
                       sead::Buffer<sead::FixedSafeString<256>>, sead::Buffer<sead::Vector2f>,
                       sead::Buffer<sead::Vector3f>, sead::Buffer<sead::Vector4f>>();
}

template <typename T>
constexpr bool isValidFlagValueType() {
    return IsAnyOfType<T, bool, s32, f32, sead::FixedSafeString<32>, sead::FixedSafeString<64>,
                       sead::FixedSafeString<256>, sead::Vector2f, sead::Vector3f,
                       sead::Vector4f>();
}

template <typename T>
constexpr bool isValidFlagType() {
    return isValidFlagValueType<T>() || isValidFlagArrayType<T>();
}

class FlagBase {
public:
    virtual ~FlagBase() = 0;

    virtual u32 getHash() const = 0;
    virtual void setHash(u32 hash) = 0;

    virtual FlagType getType() const = 0;
    virtual void setType(FlagType type) = 0;

    virtual const FlagProperties& getProperties() const = 0;
    virtual void setProperties(const FlagProperties& properties) = 0;

    virtual void resetToInitialValue() = 0;
    virtual bool isInitialValue() const = 0;

    virtual u32 getCategory() const = 0;
    virtual void setCategory(u32 category) = 0;

    virtual const sead::SafeString& getName() const = 0;
    virtual s32 getDeleteRev() const = 0;

    virtual u32 getRandomResetData() const = 0;

    bool isResettable() const { return isResettableFlag(getResetType()); }

    bool isPermanent() const {
        return isSave() && getResetType() == ResetType::NoReset && getRandomResetData() == 0;
    }

    bool isProgramReadable() const { return getProperties().isProgramReadable(); }
    bool isProgramWritable() const { return getProperties().isProgramWritable(); }
    bool isSave() const { return getProperties().isSave(); }
    bool isOneTrigger() const { return getProperties().isOneTrigger(); }
    bool isEventAssociated() const { return getProperties().isEventAssociated(); }
    ResetType getResetType() const { return getProperties().getResetType(); }

protected:
    s32 clampValue_(const s32& min_value, s32* value, const s32& max_value);
    s32 clampValue_(const f32& min_value, f32* value, const f32& max_value);
    s32 clampValue_(const sead::SafeString& min_value, sead::SafeString* value,
                    const sead::SafeString& max_value);
    s32 clampValue_(const sead::Vector2f& min_value, sead::Vector2f* value,
                    const sead::Vector2f& max_value);
    s32 clampValue_(const sead::Vector3f& min_value, sead::Vector3f* value,
                    const sead::Vector3f& max_value);
    s32 clampValue_(const sead::Vector4f& min_value, sead::Vector4f* value,
                    const sead::Vector4f& max_value);

    bool isBoolean_() const;
    u32 getCategoryForBool_(const void* data) const;
    void setCategoryForBool_(void* data, u32 category) const;
};

template <typename T>
struct FlagConfig {
    FlagConfig& operator=(const FlagConfig& other) {
        initial_value = other.initial_value;
        min_value = other.min_value;
        max_value = other.max_value;
        return *this;
    }

    T initial_value;
    T min_value;
    T max_value;
};

template <>
struct FlagConfig<bool> {
    u8 initial_value;
};

template <typename T>
class FlagT : public FlagBase {
public:
    using ConfigType = FlagConfig<T>;
    using RawValueType = std::conditional_t<std::is_same_v<T, bool>, u8, T>;

    u32 getRandomResetData() const override;

    virtual const ConfigType& getConfig() const = 0;
    virtual void setConfig(const ConfigType& config) = 0;

    virtual T getValue() const = 0;

    virtual RawValueType& getValueRef() = 0;
    virtual const RawValueType& getValueRef() const = 0;

    virtual bool hasValue(const T& value) const = 0;
    virtual bool setValue(T value) = 0;

    virtual FlagDebugData* getDebugData() const = 0;
};

template <typename T>
class Flag : public FlagT<T> {
public:
    using ConfigType = FlagConfig<T>;
    using RawValueType = std::conditional_t<std::is_same_v<T, bool>, u8, T>;

    Flag() = default;
    ~Flag() override = default;

    u32 getHash() const override;
    void setHash(u32 hash) override;

    FlagType getType() const override;
    void setType(FlagType type) override;

    const FlagProperties& getProperties() const override;
    void setProperties(const FlagProperties& properties) override;

    void resetToInitialValue() override;
    bool isInitialValue() const override;

    u32 getCategory() const override;
    void setCategory(u32 category) override;

    const sead::SafeString& getName() const override;
    s32 getDeleteRev() const override;

    const ConfigType& getConfig() const override;
    void setConfig(const ConfigType& config) override;

    T getValue() const override;

    RawValueType& getValueRef() override;
    const RawValueType& getValueRef() const override;

    bool hasValue(const T& value) const override;
    bool setValue(T value) override;

    FlagDebugData* getDebugData() const override;
    void setDebugData(FlagDebugData* data);

private:
    sead::SizedEnum<typename FlagType::ValueType, u8> mType = FlagType::Invalid;
    FlagProperties mProperties;
    ConfigType mConfig{};
    RawValueType mValue{};
    u32 mHash = 0;
    FlagDebugData* mDebugData = nullptr;
};

using FlagBool = Flag<bool>;
using FlagS32 = Flag<s32>;
using FlagF32 = Flag<f32>;
using FlagString = Flag<sead::FixedSafeString<32>>;
using FlagString64 = Flag<sead::FixedSafeString<64>>;
using FlagString256 = Flag<sead::FixedSafeString<256>>;
using FlagVector2f = Flag<sead::Vector2f>;
using FlagVector3f = Flag<sead::Vector3f>;
using FlagVector4f = Flag<sead::Vector4f>;

using FlagBoolArray = sead::Buffer<FlagBool>;
using FlagS32Array = sead::Buffer<FlagS32>;
using FlagF32Array = sead::Buffer<FlagF32>;
using FlagStringArray = sead::Buffer<FlagString>;
using FlagString64Array = sead::Buffer<FlagString64>;
using FlagString256Array = sead::Buffer<FlagString256>;
using FlagVector2fArray = sead::Buffer<FlagVector2f>;
using FlagVector3fArray = sead::Buffer<FlagVector3f>;
using FlagVector4fArray = sead::Buffer<FlagVector4f>;

KSYS_CHECK_SIZE_NX150(FlagBool, 0x18);
KSYS_CHECK_SIZE_NX150(FlagS32, 0x28);
KSYS_CHECK_SIZE_NX150(FlagF32, 0x28);
KSYS_CHECK_SIZE_NX150(FlagString, 0x100);
KSYS_CHECK_SIZE_NX150(FlagString64, 0x180);
KSYS_CHECK_SIZE_NX150(FlagString256, 0x480);
KSYS_CHECK_SIZE_NX150(FlagVector2f, 0x38);
KSYS_CHECK_SIZE_NX150(FlagVector3f, 0x48);
KSYS_CHECK_SIZE_NX150(FlagVector4f, 0x58);

inline FlagBase::~FlagBase() = default;

template <typename T>
inline u32 Flag<T>::getHash() const {
    return mHash;
}

template <typename T>
inline void Flag<T>::setHash(u32 hash) {
    mHash = hash;
}

template <typename T>
inline FlagType Flag<T>::getType() const {
    return mType.mValue;
}

template <typename T>
inline void Flag<T>::setType(FlagType type) {
    mType.mValue = u8(type);
}

template <typename T>
inline const FlagProperties& Flag<T>::getProperties() const {
    return mProperties;
}

template <typename T>
inline void Flag<T>::setProperties(const FlagProperties& properties) {
    mProperties = properties;
}

template <typename T>
inline void Flag<T>::resetToInitialValue() {
    if constexpr (std::is_same<T, bool>()) {
        const auto category = getCategory();
        mValue = getConfig().initial_value & 1;
        setCategory(category);
    } else {
        mValue = getConfig().initial_value;
    }
}

template <typename T>
inline bool Flag<T>::isInitialValue() const {
    if constexpr (std::is_same<T, bool>()) {
        const bool initial_value = getConfig().initial_value & 1;
        return getValue() == initial_value;
    } else {
        T initial_value;
        initial_value = getConfig().initial_value;
        return getValue() == initial_value;
    }
}

template <typename T>
inline u32 Flag<T>::getCategory() const {
    if (!this->isBoolean_())
        return 0;
    return this->getCategoryForBool_(&mValue);
}

template <typename T>
inline void Flag<T>::setCategory(u32 category) {
    if (!this->isBoolean_())
        return;
    this->setCategoryForBool_(&mValue, category);
}

template <typename T>
inline const sead::SafeString& Flag<T>::getName() const {
    return mDebugData ? mDebugData->name : sead::SafeString::cEmptyString;
}

template <typename T>
inline s32 Flag<T>::getDeleteRev() const {
    return mDebugData ? mDebugData->delete_rev : -1;
}

template <typename T>
inline u32 FlagT<T>::getRandomResetData() const {
    const auto& initial_value = getConfig().initial_value;
    if constexpr (std::is_same<T, bool>())
        return initial_value >> 1;
    else
        return 0;
}

template <typename T>
inline const typename Flag<T>::ConfigType& Flag<T>::getConfig() const {
    return mConfig;
}

template <typename T>
inline void Flag<T>::setConfig(const ConfigType& config) {
    mConfig = config;
}

template <typename T>
inline T Flag<T>::getValue() const {
    if constexpr (std::is_same<T, bool>())
        return mValue & 1;
    else
        return mValue;
}

template <typename T>
inline typename Flag<T>::RawValueType& Flag<T>::getValueRef() {
    return mValue;
}

template <typename T>
inline const typename Flag<T>::RawValueType& Flag<T>::getValueRef() const {
    return mValue;
}

template <typename T>
inline bool Flag<T>::hasValue(const T& value) const {
    return value == getValue();
}

template <typename T>
inline bool Flag<T>::setValue(T value) {
    if constexpr (std::is_same<T, bool>()) {
        if (value == getValue())
            return false;

        if (value)
            mValue |= 1;
        else
            mValue &= ~1;

        return true;
    } else {
        [[maybe_unused]] const T new_value = value;

        T min_value;
        T max_value;
        min_value = getConfig().min_value;
        max_value = getConfig().max_value;
        this->clampValue_(min_value, &value, max_value);

        if (mValue != value) {
            mValue = value;
            return true;
        }
        return false;
    }
}

template <typename T>
inline FlagDebugData* Flag<T>::getDebugData() const {
    return mDebugData;
}

template <typename T>
inline void Flag<T>::setDebugData(FlagDebugData* data) {
    mDebugData = data;
}

}  // namespace ksys::gdt
