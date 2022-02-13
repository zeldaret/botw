#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"

namespace ksys::phys {

class PolytopeShape;

struct CharacterPrismShapeParam {
    float radius;
    sead::Vector3f translate_0;
    sead::Vector3f translate_1;
    CommonShapeParam common;
};

class CharacterPrismShape : public Shape {
    SEAD_RTTI_OVERRIDE(CharacterPrismShape, Shape)
public:
    static CharacterPrismShape* make(const CharacterPrismShapeParam& param, sead::Heap* heap);
    CharacterPrismShape* clone(sead::Heap* heap) const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    PolytopeShape* getUnderlyingShape() const { return mShape; }

private:
    /// The underlying shape for this character prism shape.
    PolytopeShape* mShape{};
};

}  // namespace ksys::phys
