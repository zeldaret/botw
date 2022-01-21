#include "KingSystem/Physics/System/physRigidContactPoints.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

RigidContactPoints* RigidContactPoints::make(sead::Heap* heap, int num,
                                             const sead::SafeString& name, int a, int b, int c) {
    return System::instance()->allocContactPoints(heap, num, name, a, b, c);
}

void RigidContactPoints::free(RigidContactPoints* instance) {
    System::instance()->freeContactPoints(instance);
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
