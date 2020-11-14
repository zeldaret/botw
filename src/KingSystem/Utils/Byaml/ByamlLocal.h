#pragma once

#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Byaml/ByamlStringTableIter.h"

#include <basis/seadTypes.h>

namespace al::ByamlLocalUtil {

inline ByamlStringTableIter getHashKeyTableIter(const u8* data) {
    auto* header = reinterpret_cast<const al::ByamlHeader*>(data);
    const u8* ptr = &data[header->getHashKeyTableOffset()];
    return ByamlStringTableIter(ptr);
}

inline ByamlStringTableIter getStringTableIter(const u8* data) {
    auto* header = reinterpret_cast<const al::ByamlHeader*>(data);
    const u8* ptr = &data[header->getStringTableOffset()];
    return ByamlStringTableIter(ptr);
}

inline s32 getContainerSize(const u8* data) {
    auto* node = reinterpret_cast<const al::ByamlContainerHeader*>(data);
    return node->getCount();
}

inline al::ByamlType getType(const u8* data) {
    auto* node = reinterpret_cast<const al::ByamlContainerHeader*>(data);
    return node->getType();
}

const char* getDataTypeString(s32 type);

bool verifiByaml(const u8* data);
bool verifiByamlHeader(const u8* data);
bool verifiByamlStringTable(const u8* data);

}  // namespace al::ByamlLocalUtil
