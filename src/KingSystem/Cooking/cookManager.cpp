#include "KingSystem/Cooking/cookManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys {

CookingMgr::CookingMgr() {}

SEAD_SINGLETON_DISPOSER_IMPL(CookingMgr)

CookingMgr::~CookingMgr() {
    if (mConfig) {
        delete mConfig;
        mConfig = nullptr;
    }
}

void CookingMgr::getCookItem(CookItem& to) {
    return to.copy(mCookItem);
}

}  // namespace ksys
