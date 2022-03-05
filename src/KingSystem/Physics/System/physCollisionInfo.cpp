#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

CollisionInfo* CollisionInfo::make(sead::Heap* heap, const sead::SafeString& name) {
    return System::instance()->allocCollisionInfo(heap, name);
}

void CollisionInfo::free(CollisionInfo* info) {
    System::instance()->freeCollisionInfo(info);
}

CollisionInfo::CollisionInfo(const sead::SafeString& name) : sead::INamable(name) {
    mCollidingBodies.initOffset(CollidingBodies::getListNodeOffset());
}

CollisionInfo::~CollisionInfo() {
    mCollidingBodies.clear();
}

}  // namespace ksys::phys
