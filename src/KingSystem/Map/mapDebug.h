#pragma once

#include <prim/seadSafeString.h>

namespace ksys::map {

class Object;

bool printDebugMsg(Object* object, const sead::SafeString& msg, const char* config_name);

}  // namespace ksys::map
