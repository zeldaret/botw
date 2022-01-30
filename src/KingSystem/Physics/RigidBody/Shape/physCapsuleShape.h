#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Physics/System/physMaterialMask.h"

class hkpShape;

namespace ksys::phys {

class CapsuleParam;
struct CapsuleShape;

struct CapsuleShapeParam {
    CapsuleShape* createShape(sead::Heap* heap);

    sead::Vector3f vertex_a;
    sead::Vector3f vertex_b;
    f32 radius;
    u32 _1c;
    Material material;
    const char* sub_material = sead::SafeString::cEmptyString.cstr();
    FloorCode floor_code;
    WallCode wall_code;
    bool _38 = false;
};

struct CapsuleShape : Shape {
    SEAD_RTTI_OVERRIDE(CapsuleShape, Shape)
public:
    enum class Flag {
        Modified = 1 << 0,
    };

    CapsuleShape(const CapsuleShapeParam& shape_, hkpShape* hkp_shape_);
    ~CapsuleShape() override;

    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    void updateHavokShape() override;
    void setScale(float scale) override;

    RigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);
    CapsuleShape* clone(sead::Heap* heap);
    f32 getRadius() const;
    void getVertices(sead::Vector3f* va, sead::Vector3f* vb) const;
    bool setRadius(f32 r);
    bool setVertices(const sead::Vector3f& va, const sead::Vector3f& vb);
    f32 getVolume() const;
    void sub_7100FABE80(sead::Vector3f* veca, sead::Vector3f* vecb, const hkTransformf& rb_vec);
    void setMaterialMask(const MaterialMask& mask);

    sead::Vector3f vertex_a;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> flags{};
    sead::Vector3f vertex_b;
    f32 radius;
    MaterialMask material_mask;
    hkpShape* shape;
};

class CapsuleParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(CapsuleParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    CapsuleShapeParam shape;
};

}  // namespace ksys::phys
