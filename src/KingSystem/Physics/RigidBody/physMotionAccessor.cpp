#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

MotionAccessor::MotionAccessor(RigidBody* body) : mBody(body) {}

MotionAccessor::~MotionAccessor() = default;

MotionType MotionAccessor::getMotionInfo() const {
    return mBody->getMotionInfo();
}

hkpMotion* MotionAccessor::getMotion() const {
    return mBody->getMotion();
}

void MotionAccessor::setMotionFlag(RigidBody::MotionFlag flag) {
    mBody->setMotionFlag(flag);
}

bool MotionAccessor::hasMotionSet(RigidBody::MotionFlag flag) const {
    return mBody->getMotionFlags().isOn(flag);
}

bool MotionAccessor::hasMotionDisabled(RigidBody::MotionFlag flag) const {
    return mBody->getMotionFlags().isOff(flag);
}

void MotionAccessor::disableMotionFlag(RigidBody::MotionFlag flag) {
    mBody->resetMotionFlagDirect(flag);
}

}  // namespace ksys::phys
