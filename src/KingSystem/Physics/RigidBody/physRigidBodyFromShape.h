#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class MaterialMask;
class Shape;

class RigidBodyFromShape : public RigidBody {
    SEAD_RTTI_OVERRIDE(RigidBodyFromShape, RigidBody)
public:
    /// Create a RigidBodyFromShape with the specified shape and rigid body parameters.
    /// @param shape Must not be null.
    template <typename RigidBodyT, typename ShapeT>
    static RigidBodyT* make(ShapeT* shape, bool set_flag_10, const RigidBodyInstanceParam& param,
                            sead::Heap* heap);

    RigidBodyFromShape(hkpRigidBody* hkp_rigid_body, ContactLayerType layer_type,
                       const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~RigidBodyFromShape() override;

    const MaterialMask* tryGetMaterialMask() const;

protected:
    const hkpShape* getNewHavokShape_() override;
    float updateScale_(float scale, float old_scale) override;

    virtual Shape* getShape_() = 0;
    virtual const Shape* getShape_() const = 0;
};

}  // namespace ksys::phys
