#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

// FIXME
class TeraMeshRigidBody : public RigidBody {
public:
    TeraMeshRigidBody(hkpRigidBody* hk_body, sead::Heap* heap);
};

}  // namespace ksys::phys
