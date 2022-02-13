#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

enum class ShapeType;
class MaterialMask;
class Shape;
struct RigidBodyInstanceParam;

class BoxRigidBody;
class BoxWaterRigidBody;
class CapsuleRigidBody;
class CylinderRigidBody;
class CylinderWaterRigidBody;
class ListShapeRigidBody;
class PolytopeRigidBody;
class SphereRigidBody;

class BoxShape;
class BoxWaterShape;
struct CapsuleShape;
class CylinderShape;
class CylinderWaterShape;
class ListShape;
class PolytopeShape;
class SphereShape;

class RigidBodyFromShape : public RigidBody {
    SEAD_RTTI_OVERRIDE(RigidBodyFromShape, RigidBody)
public:
    static SphereRigidBody* createSphere(RigidBodyInstanceParam* param, sead::Heap* heap);
    static CapsuleRigidBody* createCapsule(RigidBodyInstanceParam* param, sead::Heap* heap);
    static CylinderRigidBody* createCylinder(RigidBodyInstanceParam* param, sead::Heap* heap);
    static CylinderWaterRigidBody* createCylinderWater(RigidBodyInstanceParam* param,
                                                       sead::Heap* heap);
    static BoxRigidBody* createBox(RigidBodyInstanceParam* param, sead::Heap* heap);
    static BoxWaterRigidBody* createBoxWater(RigidBodyInstanceParam* param, sead::Heap* heap);
    static PolytopeRigidBody* createPolytope(RigidBodyInstanceParam* param, sead::Heap* heap);
    static ListShapeRigidBody* createList(RigidBodyInstanceParam* param, sead::Heap* heap);

    RigidBody* clone(sead::Heap* heap, SystemGroupHandler* group_handler) const;

    static RigidBody* create(const Shape& shape, RigidBodyInstanceParam* param, sead::Heap* heap,
                             const SystemGroupHandler* group_handler);

    static RigidBody* createEntityShapeBody(const sead::SafeString& name, ContactLayer layer,
                                            RigidBodyFromShape* linked_body, sead::Heap* heap,
                                            SystemGroupHandler* group_handler);

    RigidBodyFromShape(hkpRigidBody* hkp_rigid_body, ContactLayerType layer_type,
                       const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~RigidBodyFromShape() override;

    ShapeType getShapeType() const;
    const MaterialMask* tryGetMaterialMask() const;

protected:
    const hkpShape* getNewHavokShape_() override;
    float updateScale_(float scale, float old_scale) override;

    virtual Shape* getShape_() = 0;
    virtual const Shape* getShape_() const = 0;

private:
    /// Create a RigidBodyFromShape with the specified rigid body parameters.
    /// @param param Must be an instance of ParamT.
    template <typename RigidBodyT, typename ShapeT, typename ParamT>
    static inline RigidBodyT* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    /// Create a RigidBodyFromShape with the specified shape and rigid body parameters.
    /// @param shape Must not be null.
    template <typename RigidBodyT, typename ShapeT>
    static RigidBodyT* make(ShapeT* shape, bool set_flag_10, const RigidBodyInstanceParam& param,
                            sead::Heap* heap);

    /// Create a RigidBodyFromShape with the specified shape, rigid body parameters and handler.
    template <typename RigidBodyT, typename ShapeT>
    static RigidBodyT* make(const Shape& shape, RigidBodyInstanceParam* param, sead::Heap* heap,
                            const SystemGroupHandler* group_handler);

    template <typename RigidBodyT, typename ShapeT, typename ParamT>
    RigidBodyT* cloneImpl(sead::Heap* heap, SystemGroupHandler* group_handler) const;

    template <typename RigidBodyT, typename ShapeT, typename ParamT>
    static RigidBodyT* createEntityShapeBodyImpl(const sead::SafeString& name, ContactLayer layer,
                                                 RigidBodyFromShape* linked_body, sead::Heap* heap,
                                                 SystemGroupHandler* group_handler);
};

}  // namespace ksys::phys
