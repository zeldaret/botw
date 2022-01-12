#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

class hkpMotion;

namespace ksys::phys {

class MotionAccessor {
    SEAD_RTTI_BASE(MotionAccessor)
public:
    explicit MotionAccessor(RigidBody* body);
    virtual ~MotionAccessor();

    MotionType getMotionInfo() const;
    hkpMotion* getMotion() const;
    void setMotionFlag(RigidBody::MotionFlag flag);
    bool hasMotionFlagSet(RigidBody::MotionFlag flag) const;
    bool hasMotionFlagDisabled(RigidBody::MotionFlag flag) const;
    void disableMotionFlag(RigidBody::MotionFlag flag);

private:
    RigidBody* mBody;
    void* _10 = nullptr;
};

}  // namespace ksys::phys
