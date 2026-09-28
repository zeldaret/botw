#include "KingSystem/System/CurrentResNameMgr.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(CurrentResNameMgr)

void CurrentResNameMgr::init(sead::Heap*) {}

sead::SafeString CurrentResNameMgr::getCurrentResName() const {
    return sead::SafeString::cEmptyString;
}

}  // namespace ksys
