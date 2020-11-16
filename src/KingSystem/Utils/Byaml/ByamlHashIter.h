#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "prim/seadEndian.h"

namespace al {

struct ByamlData;
struct ByamlHashPair;

class ByamlHashIter {
public:
    explicit ByamlHashIter(const u8* data);

    s32 getSize() const;
    const ByamlHashPair* getPairTable() const;
    bool getDataByIndex(ByamlData* data, s32 index) const;
    bool getDataByKey(ByamlData* data, s32 key_index) const;
    const ByamlHashPair* findPair(s32 key_index) const;
    const ByamlHashPair* getPairByIndex(s32 index) const;

private:
    const u8* mData;

    static constexpr s32 mTableOffset = 4;
};

struct ByamlHashPair {
    u32 getKey() const { return mKeyAndType & 0xFFFFFF; }
    ByamlType getType() const { return ByamlType(mKeyAndType >> 24); }
    u32 getValue() const { return mValue; }

    u32 mKeyAndType;
    u32 mValue;
};

}  // namespace al
