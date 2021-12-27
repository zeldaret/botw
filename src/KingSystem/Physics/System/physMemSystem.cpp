#include "KingSystem/Physics/System/physMemSystem.h"
#include "KingSystem/Physics/System/physContactMgr.h"

namespace ksys::phys {

SEAD_SINGLETON_DISPOSER_IMPL(MemSystem)

RigidContactPoints* MemSystem::allocContactPoints(sead::Heap* heap, int num,
                                                  const sead::SafeString& name, int a, int b,
                                                  int c) const {
    return mContactMgr->allocContactPoints(heap, num, name, a, b, c);
}

void MemSystem::freeContactPoints(RigidContactPoints* points) const {
    mContactMgr->freeContactPoints(points);
}

void MemSystem::registerContactPoints(RigidContactPoints* points) const {
    mContactMgr->registerContactPoints(points);
}

}  // namespace ksys::phys
