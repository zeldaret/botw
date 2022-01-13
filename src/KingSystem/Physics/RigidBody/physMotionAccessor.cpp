#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

MotionAccessor::MotionAccessor(RigidBody* body) : mBody(body) {}

MotionAccessor::~MotionAccessor() = default;

MotionType MotionAccessor::getMotionType() const {
    return mBody->getMotionType();
}

hkpMotion* MotionAccessor::getRigidBodyMotion() const {
    return mBody->getMotion();
}

void MotionAccessor::setMotionFlag(RigidBody::MotionFlag flag) {
    mBody->setMotionFlag(flag);
}

bool MotionAccessor::hasMotionFlagSet(RigidBody::MotionFlag flag) const {
    return mBody->getMotionFlags().isOn(flag);
}

bool MotionAccessor::hasMotionFlagDisabled(RigidBody::MotionFlag flag) const {
    return mBody->getMotionFlags().isOff(flag);
}

void MotionAccessor::disableMotionFlag(RigidBody::MotionFlag flag) {
    mBody->resetMotionFlagDirect(flag);
}

}  // namespace ksys::phys
