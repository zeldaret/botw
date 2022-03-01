#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"

namespace ksys::phys {

ContactLayerCollisionInfo::ContactLayerCollisionInfo(ContactLayer layer) : mLayer(layer) {
    // FIXME: figure out what this is
    mList.initOffset(0x10);
}

ContactLayerCollisionInfo::~ContactLayerCollisionInfo() = default;

}  // namespace ksys::phys
