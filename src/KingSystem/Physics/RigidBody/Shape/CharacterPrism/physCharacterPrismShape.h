#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

class PolytopeShape;

struct CharacterPrismShapeParam {
    float radius = 0.35;
    float ring0_distance = 0.5;
    float ring1_distance = 1.5;
    float end_vertex_distance = 1.8;
    sead::Vector3f offset = sead::Vector3f::zero;
    CommonShapeParam common;
};

/// A "stretched bipyramid" shape with a top and bottom vertex and two rings of eight vertices
/// between them.
class CharacterPrismShape : public Shape {
    SEAD_RTTI_OVERRIDE(CharacterPrismShape, Shape)

public:
    ~CharacterPrismShape() override;

    static CharacterPrismShape* make(const CharacterPrismShapeParam& param, sead::Heap* heap);
    CharacterPrismShape* clone(sead::Heap* heap) const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    ShapeType getType() const override { return ShapeType::CharacterPrism; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;

    PolytopeShape* getUnderlyingShape() const { return mShape; }

private:
    static constexpr int RING_VERTEX_NUM = 8;
    static constexpr int SHAPE_VERTEX_NUM = RING_VERTEX_NUM * 2 + 2;

    /// The underlying shape for this character prism shape.
    PolytopeShape* mShape{};

    float mRadius;
    float mRing0Distance;
    float mRing1Distance;
    float mEndVertexDistance;
    sead::Vector3f mOffset;
    float mScale;
};

}  // namespace ksys::phys
