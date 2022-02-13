#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkpConvexTransformShape;
class hkpConvexVerticesShape;

namespace ksys::phys {

struct PolytopeShapeParam {
    /// Number of vertices.
    u16 vertex_num = 32;
    CommonShapeParam common;
};

class PolytopeShape : public Shape {
    SEAD_RTTI_OVERRIDE(PolytopeShape, Shape)
public:
    enum class Flag {
        _1 = 1 << 0,
        InvalidVolume = 1 << 1,
        _4 = 1 << 2,
        HasCustomScale = 1 << 3,
        _10 = 1 << 4,
    };

    static PolytopeShape* make(const PolytopeShapeParam& param, sead::Heap* heap);
    PolytopeShape* clone(sead::Heap* heap) const;

    explicit PolytopeShape(const PolytopeShapeParam& param);
    ~PolytopeShape() override;

    const sead::Vector3f& getVertex(int vertex_idx) const { return mVertices[vertex_idx]; }
    bool setVertex(int vertex_idx, const sead::Vector3f& vertex);
    u16 getNumVertices() const { return mNumVertices; }
    void setNumVertices(u16 num);

    ShapeType getType() const override { return ShapeType::Polytope; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;

    void setScale(float scale) override;
    float getScale() const { return mScale; }

    void setVolume(float volume);

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const { return mMaterialMask; }

private:
    bool init(const PolytopeShapeParam& param, sead::Heap* heap);

    sead::CriticalSection mCS;
    hkpConvexVerticesShape* mHavokShape{};
    hkpConvexTransformShape* mTransformShape{};
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    MaterialMask mMaterialMask;
    float mVolume = -1.0;
    float mScale = 1.0;
    sead::Buffer<sead::Vector3f> mVertices;
    u16 mNumVertices{};
};

constexpr PolytopeShape::Flag operator|(PolytopeShape::Flag a, PolytopeShape::Flag b) {
    return PolytopeShape::Flag(u32(a) | u32(b));
}

class PolytopeParam : public RigidBodyInstanceParam, public PolytopeShapeParam {
    SEAD_RTTI_OVERRIDE(PolytopeParam, RigidBodyInstanceParam)
public:
    PolytopeParam() : RigidBodyInstanceParam(ShapeType::Polytope) {}
};

}  // namespace ksys::phys
