#include "KingSystem/Utils/Byaml/ByamlStringTableIter.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlLocal.h"

namespace al {

ByamlStringTableIter::ByamlStringTableIter(const u8* data) {
    mData = data;
}

ByamlStringTableIter::ByamlStringTableIter(const ByamlStringTableIter& other) {
    mData = other.mData;
}

const char* ByamlStringTableIter::getString(s32 index) const {
    const u32* string_offset_array = getStringOffsetArray();
    return reinterpret_cast<const char*>(&mData[string_offset_array[index]]);
}

s32 ByamlStringTableIter::findStringIndex(const char* string) const {
    const u32* string_offset_array = getStringOffsetArray();
    u32 table_size = ByamlLocalUtil::getContainerSize(mData);
    if (table_size == 0) {
        return -1;
    }

    // Binary Search
    s32 start = 0;
    s32 end = table_size;
    s32 index;
    while (true) {
        if (start >= end) {
            return -1;
        }

        index = (start + end) / 2;
        const char* str = reinterpret_cast<const char*>(&mData[string_offset_array[index]]);
        s32 result = std::strcmp(string, str);
        if (result == 0)
            break;
        if (result > 0)
            start = index + 1;
        else if (result < 0)
            end = index;
    }

    return index;
}

}  // namespace al
