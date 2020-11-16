#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlHashIter.h"

namespace al {

struct ByamlData {
    ByamlData();

    explicit ByamlData(const ByamlHashPair* pair) : ByamlData{} { set(pair); }

    template <typename T = u32>
    T getValue() const {
        return *reinterpret_cast<const T*>(&mValue);
    }
    ByamlType getType() const { return mType; }

    void set(const ByamlHashPair* pair) {
        mType = pair->getType();
        mValue = pair->getValue();
    }
    template <typename T = u32>
    void set(const ByamlType& type, const T& value) {
        mType = type;
        mValue = *reinterpret_cast<const u32*>(&value);
    }

    void setType(const ByamlType& type) { mType = type; }

    template <typename T = u32>
    void setValue(const T& value) {
        mValue = *reinterpret_cast<const u32*>(&value);
    }

    void clear() {
        mValue = 0;
        mType = ByamlType::Invalid;
    }

private:
    u32 mValue = 0;
    sead::SizedEnum<ByamlType, u8> mType = ByamlType::Invalid;
};

}  // namespace al
