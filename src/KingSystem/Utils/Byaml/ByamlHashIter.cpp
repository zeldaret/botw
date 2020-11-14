#include "KingSystem/Utils/Byaml/ByamlHashIter.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlData.h"
#include "KingSystem/Utils/Byaml/ByamlLocal.h"

namespace al {

ByamlHashIter::ByamlHashIter(const u8* data) {
    mData = data;
}

s32 ByamlHashIter::getSize() const {
    if (!mData) {
        return 0;
    }

    return ByamlLocalUtil::getContainerSize(mData);
}

const ByamlHashPair* ByamlHashIter::getPairTable() const {
    if (!mData) {
        return nullptr;
    }

    return reinterpret_cast<const ByamlHashPair*>(&mData[mTableOffset]);
}

bool ByamlHashIter::getDataByIndex(ByamlData* data, s32 index) const {
    if (!mData) {
        return false;
    }

    if (ByamlLocalUtil::getContainerSize(mData) == 0) {
        return false;
    }

    const ByamlHashPair* pair_table = getPairTable();
    const ByamlHashPair* pair = &pair_table[index];
    if (!pair)  // This seems wrong, this can never be null?
    {
        return false;
    }

    data->set(pair);

    return true;
}

bool ByamlHashIter::getDataByKey(ByamlData* data, s32 key_index) const {
    if (getSize() == 0) {
        return false;
    }

    const ByamlHashPair* pair = findPair(key_index);
    if (!pair) {
        return false;
    }

    data->set(pair);
    return true;
}

const ByamlHashPair* ByamlHashIter::findPair(s32 key_index) const {
    const ByamlHashPair* pair_table = getPairTable();
    if (!pair_table) {
        return nullptr;
    }

    if (ByamlLocalUtil::getContainerSize(mData) == 0) {
        return nullptr;
    }

    // Binary Search
    s32 start = 0;
    s32 end = getSize();
    s32 index;
    const ByamlHashPair* pair;
    while (true) {
        if (start >= end) {
            return nullptr;
        }

        index = (start + end) / 2;
        pair = &pair_table[index];
        s32 result = key_index - pair->getKey();
        if (result == 0)
            break;
        if (result > 0)
            start = index + 1;
        else if (result < 0)
            end = index;
    }

    return pair;
}

const ByamlHashPair* ByamlHashIter::getPairByIndex(s32 index) const {
    if (index < 0) {
        return nullptr;
    }

    if (getSize() <= index) {
        return nullptr;
    }

    const ByamlHashPair* pair_table = getPairTable();
    return pair_table + index;
}

}  // namespace al
