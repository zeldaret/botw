#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class Constraint;
}

namespace ksys::act {

class Actor;

class PhysicsConstraints {
public:
    PhysicsConstraints();
    ~PhysicsConstraints();

    bool initialize(Actor* actor, sead::Heap* heap);
    void finalize();
    void calc();

private:
    sead::Buffer<phys::Constraint*> mConstraints;
    bool _10 = false;
    bool _11 = false;
};
KSYS_CHECK_SIZE_NX150(PhysicsConstraints, 0x18);

}  // namespace ksys::act
