#pragma once

#include <basis/seadTypes.h>

namespace alByamlLocalUtil {

const char* getDataTypeString(s32 type);

const u8* getHashKeyTable(const u8* data);
const u8* getStringTable(const u8* data);

bool verifiByaml(const u8* data);
bool verifiByamlHeader(const u8* data);
bool verifiByamlStringTable(const u8* data);

}  // namespace alByamlLocalUtil
