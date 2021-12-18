#pragma once

#include <Havok/Common/Base/Math/Vector/hkVector4.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

class hkpShape;

namespace ksys::phys {

class CapsuleView;
struct CapsuleShape;

struct CapsuleBody {
    enum class Flag {
        Modified = 1 << 0,
    };

    struct Unk {
        Unk(u32 a1, const char* a2, u32 a3, u32 a4, u32 a5);
        virtual ~Unk();

        u32 shape_type = 0;
        const char* _10;
    };

    CapsuleBody(const sead::Vector3f& va, const sead::Vector3f& vb, f32 r, u32 a4, const char* a5,
                u32 a6, u32 a7, hkpShape* a8)
        : vertex_a(va), vertex_b(vb), radius(r), unk(a4, a5, a6, a7, 0), shape(a8) {}
    virtual ~CapsuleBody();

    virtual hkpShape* getShape();
    virtual const hkpShape* getShape() const;
    virtual void updateChanges();
    virtual void scaleVerts(f32 scale);

    RigidBody* init(u32 flag, RigidBodyParamView* view, sead::Heap* heap);
    CapsuleBody* clone(sead::Heap* heap);
    f32 getRadius() const;
    void getVertices(sead::Vector3f* va, sead::Vector3f* vb) const;
    bool setRadius(f32 r);
    bool setVertices(const sead::Vector3f& va, const sead::Vector3f& vb);
    f32 getVolume() const;
    void sub_7100FABE80(sead::Vector3f* veca, sead::Vector3f* vecb, const hkVector4& rb_vec);

    sead::Vector3f vertex_a;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> flags{};
    sead::Vector3f vertex_b;
    f32 radius;
    Unk unk;
    hkpShape* shape;
};

struct CapsuleShape {
    CapsuleBody* init(sead::Heap* heap);

    sead::Vector3f vertex_a;
    sead::Vector3f vertex_b;
    f32 radius;
    u32 _1c;
    u32 _20;
    const char* _28;
    u32 _30;
    u32 _34;
    bool _38;
};

class CapsuleView : public RigidBodyParamView {
    SEAD_RTTI_OVERRIDE(CapsuleView, RigidBodyParamView)
public:
    u8 _90;
    float _94;
    CapsuleShape shape;
};

}  // namespace ksys::phys
