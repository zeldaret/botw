#include "KingSystem/Resource/resCurrentResNameMgr.h"

namespace ksys::res {

SEAD_SINGLETON_DISPOSER_IMPL(CurrentResNameMgr)

void CurrentResNameMgr::init(sead::Heap*) {}

sead::SafeString CurrentResNameMgr::getCurrentResName() const {
    return sead::SafeString::cEmptyString;
}

}  // namespace ksys::res
