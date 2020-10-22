#pragma once

#include "KingSystem/GameData/gdtFlag.h"

namespace ksys::gdt {

template <typename T>
class FlagProxy : public FlagT<T> {
public:
    using ConfigType = FlagConfig<T>;
    using RawValueType = typename Flag<T>::RawValueType;

    FlagProxy() = default;
    explicit FlagProxy(Flag<T>* flag) : mFlag(flag) {}
    ~FlagProxy() override = default;

    Flag<T>* getFlag() const { return mFlag; }
    void setFlag(Flag<T>* flag) { mFlag = flag; }

    u32 getHash() const override { return mFlag->getHash(); }
    void setHash(u32 hash) override { mFlag->setHash(hash); }

    FlagType getType() const override { return mFlag->getType(); }
    void setType(FlagType type) override { mFlag->setType(type); }

    const FlagProperties& getProperties() const override { return mFlag->getProperties(); }
    void setProperties(const FlagProperties& properties) override {
        mFlag->setProperties(properties);
    }

    void resetToInitialValue() override;
    bool isInitialValue() const override;

    u32 getCategory() const override;
    void setCategory(u32 category) override;

    const sead::SafeString& getName() const override { return mFlag->getName(); }
    s32 getDeleteRev() const override { return mFlag->getDeleteRev(); }

    const ConfigType& getConfig() const override { return mFlag->getConfig(); }
    void setConfig(const ConfigType& config) override { mFlag->setConfig(config); }

    T getValue() const override;

    RawValueType& getValueRef() override;
    const RawValueType& getValueRef() const override;

    bool hasValue(const T& value) const override;
    bool setValue(T value) override;

    FlagDebugData* getDebugData() const override { return mFlag->getDebugData(); }
    void setDebugData(FlagDebugData* data) { mFlag->setDebugData(data); }

private:
    Flag<T>* mFlag = nullptr;
    RawValueType mValue{};
};

template <typename T>
inline void FlagProxy<T>::resetToInitialValue() {
    if constexpr (std::is_same<T, bool>()) {
        const auto category = getCategory();
        mValue = getConfig().initial_value & 1;
        setCategory(category);
    } else {
        mValue = getConfig().initial_value;
    }
}

template <typename T>
inline bool FlagProxy<T>::isInitialValue() const {
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
inline u32 FlagProxy<T>::getCategory() const {
    if (!this->isBoolean_())
        return 0;
    return this->getCategoryForBool_(&mValue);
}

template <typename T>
inline void FlagProxy<T>::setCategory(u32 category) {
    if (!this->isBoolean_())
        return;
    this->setCategoryForBool_(&mValue, category);
}

template <typename T>
inline T FlagProxy<T>::getValue() const {
    if constexpr (std::is_same<T, bool>())
        return mValue & 1;
    else
        return mValue;
}

template <typename T>
inline typename FlagProxy<T>::RawValueType& FlagProxy<T>::getValueRef() {
    return mValue;
}

template <typename T>
inline const typename FlagProxy<T>::RawValueType& FlagProxy<T>::getValueRef() const {
    return mValue;
}

template <typename T>
inline bool FlagProxy<T>::hasValue(const T& value) const {
    return value == getValue();
}

template <typename T>
inline bool FlagProxy<T>::setValue(T value) {
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

}  // namespace ksys::gdt
