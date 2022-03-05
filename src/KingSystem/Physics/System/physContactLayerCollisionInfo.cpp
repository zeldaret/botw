#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"

namespace ksys::phys {

ContactLayerCollisionInfo::ContactLayerCollisionInfo(ContactLayer layer) : mLayer(layer) {
    mCollidingBodies.initOffset(CollidingBodies::getListNodeOffset());
}

ContactLayerCollisionInfo::~ContactLayerCollisionInfo() = default;

}  // namespace ksys::phys
