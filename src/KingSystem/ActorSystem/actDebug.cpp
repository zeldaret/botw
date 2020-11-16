#include "KingSystem/ActorSystem/actDebug.h"
#include <prim/seadSafeString.h>

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorDebug)

const char* ActorDebug::getNullStr(HashUnused*) {
    return &sead::SafeString::cNullChar;
}

}  // namespace ksys::act
