#include "KingSystem/Physics/System/physRigidContactPoints.h"
#include "KingSystem/Physics/System/physMemSystem.h"

namespace ksys::phys {

RigidContactPoints* RigidContactPoints::make(sead::Heap* heap, int num,
                                             const sead::SafeString& name, int a, int b, int c) {
    return MemSystem::instance()->allocContactPoints(heap, num, name, a, b, c);
}

void RigidContactPoints::free(RigidContactPoints* instance) {
    MemSystem::instance()->freeContactPoints(instance);
}

RigidContactPoints::RigidContactPoints(const sead::SafeString& name, int a, int b, int c)
    : IRigidContactPoints(name, a, b, c) {}

RigidContactPoints::~RigidContactPoints() = default;

void RigidContactPoints::allocPoints(sead::Heap* heap, int num) {
    mPoints.allocBufferAssert(num, heap);
}

void RigidContactPoints::freePoints() {
    mPoints.freeBuffer();
}

}  // namespace ksys::phys
