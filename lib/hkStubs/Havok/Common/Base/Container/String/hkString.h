#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

namespace hkString {

int strCmp(const char* s1, const char* s2);
hkBool beginsWith(const char* str, const char* prefix);
hkBool endsWith(const char* str, const char* suffix);

}  // namespace hkString
