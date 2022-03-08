#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class TerrainHeightFieldRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(TerrainHeightFieldRigidBody, RigidBody)
public:
    bool getD8() const { return _d8; }

private:
    void* _d0{};
    bool _d8 = false;
};

}  // namespace ksys::phys
