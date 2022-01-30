#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

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

const hkpShape* RigidBodyFromShape::getNewHavokShape_() {
    return getShape_()->updateHavokShape();
}

float RigidBodyFromShape::updateScale_(float scale, float old_scale) {
    if (scale == old_scale)
        return old_scale;

    // Relative scale.
    const float ratio = scale / old_scale;

    getShape_()->setScale(ratio);
    updateShape();

    setCenterOfMassInLocal(getCenterOfMassInLocal() * ratio);

    if (isEntity()) {
        const float scale3 = ratio * ratio * ratio;
        setMass(getMass() * scale3);

        const float scale5 = scale3 * ratio * ratio;
        setInertiaLocal(getInertiaLocal() * scale5);
    }

    return scale;
}

}  // namespace ksys::phys
