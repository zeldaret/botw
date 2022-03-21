#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

StaticCompoundMgr::StaticCompoundMgr() = default;

StaticCompoundMgr::~StaticCompoundMgr() {
    if (mGroupHandler) {
        System::instance()->removeSystemGroupHandler(mGroupHandler);
        mGroupHandler = nullptr;
    }
}

bool StaticCompoundMgr::init() {
    if (!mGroupHandler)
        mGroupHandler = System::instance()->addSystemGroupHandler(ContactLayerType::Entity);

    return true;
}

}  // namespace ksys::phys
