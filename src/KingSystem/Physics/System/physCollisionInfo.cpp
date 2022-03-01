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
    // FIXME: figure out what this is
    mList.initOffset(0x10);
}

CollisionInfo::~CollisionInfo() {
    mList.clear();
}

}  // namespace ksys::phys
