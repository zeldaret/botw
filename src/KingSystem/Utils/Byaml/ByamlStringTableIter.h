#pragma once

#include <basis/seadTypes.h>

namespace al {

class ByamlStringTableIter {
public:
    explicit ByamlStringTableIter(const u8* data);
    ByamlStringTableIter(const ByamlStringTableIter& other);

    const char* getString(s32 index) const;
    s32 findStringIndex(const char* string) const;

    bool isValid() const { return mData != nullptr; }

    const u32* getStringOffsetArray() const {
        return reinterpret_cast<const u32*>(&mData[TableOffset]);
    }

private:
    const u8* mData;

    static constexpr u32 TableOffset = 4u;
};

}  // namespace al