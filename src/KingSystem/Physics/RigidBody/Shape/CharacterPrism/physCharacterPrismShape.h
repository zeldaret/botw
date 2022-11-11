#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

class PolytopeShape;

struct CharacterPrismShapeParam {
    float radius = 0.35;
    sead::Vector3f translate_0 = {0.5, 1.5, 1.8};
    sead::Vector3f translate_1 = sead::Vector3f::zero;
    CommonShapeParam common;
};

class CharacterPrismShape : public Shape {
    SEAD_RTTI_OVERRIDE(CharacterPrismShape, Shape)
public:
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
    /// The underlying shape for this character prism shape.
    PolytopeShape* mShape{};

    float mRadius;
    sead::Vector3f mTranslate0;
    sead::Vector3f mTranslate1;
    float mScale;
};

}  // namespace ksys::phys
