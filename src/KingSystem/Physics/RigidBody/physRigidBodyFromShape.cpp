#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>

namespace ksys::phys {

RigidBodyFromShape::RigidBodyFromShape(hkpRigidBody* hkp_rigid_body, ContactLayerType layer_type,
                                       const sead::SafeString& name, bool set_flag_10,
                                       sead::Heap* heap)
    : RigidBody(RigidBody::Type::FromShape, layer_type, hkp_rigid_body, name, heap, set_flag_10) {}

RigidBodyFromShape::~RigidBodyFromShape() {
    mHkBody->setName(nullptr);
    mHkBody->deallocateInternalArrays();
    /// @bug This should be `delete mhkBody;` -- hkpRigidBody is not trivially destructible and
    /// calling operator delete directly does not call the destructor.
    if (mHkBody)
        operator delete(mHkBody);
}

}  // namespace ksys::phys
