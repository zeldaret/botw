#include "KingSystem/Physics/RigidBody/TeraMesh/physTeraMeshRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

TeraMeshRigidBody::TeraMeshRigidBody(hkpRigidBody* hk_body, sead::Heap* heap)
    : RigidBody(RigidBody::Type::TeraMesh, ContactLayerType::Entity, hk_body, "TeraMesh", heap,
                true) {
    RigidBodyInstanceParam param;
    param.motion_type = MotionType::Fixed;
    initMotionAccessor(param, heap, false);
}

}  // namespace ksys::phys
