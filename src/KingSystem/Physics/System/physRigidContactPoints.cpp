#include "KingSystem/Physics/System/physRigidContactPoints.h"

namespace ksys::phys {

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
