#include "KingSystem/Physics/System/physMemSystem.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physRigidContactPoints.h"

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

RigidContactPointsEx* MemSystem::allocContactPointsEx(sead::Heap* heap, int num, int num2,
                                                      const sead::SafeString& name, int a, int b,
                                                      int c) const {
    return mContactMgr->allocContactPointsEx(heap, num, num2, name, a, b, c);
}

void MemSystem::registerContactPoints(RigidContactPoints* points) const {
    mContactMgr->registerContactPoints(points);
}

}  // namespace ksys::phys
