#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"

namespace ksys::phys {

void CharacterPrismShape::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& CharacterPrismShape::getMaterialMask() const {
    return mShape->getMaterialMask();
}

CharacterPrismShape* CharacterPrismShape::make(const CharacterPrismShapeParam& param,
                                               sead::Heap* heap) {
    PolytopeShapeParam polytopeShapeParam;
    polytopeShapeParam.common = param.common;
    auto* polytopeShape = PolytopeShape::make(polytopeShapeParam, heap);
    auto *shape = new (heap) CharacterPrismShape();
    shape->mShape = polytopeShape;
    shape->mRadius = param.radius;
    shape->mTranslate0 = param.translate_0;
    shape->mTranslate1 = param.translate_1;
    return shape;
}

CharacterPrismShape* CharacterPrismShape::clone(sead::Heap* heap) const {
    CharacterPrismShapeParam param;
    auto *cloned = make(param, heap);
    cloned->mShape = mShape->clone(heap);
    return cloned;
}

float CharacterPrismShape::getVolume() const {
    return mShape->getVolume();
}

hkpShape* CharacterPrismShape::getHavokShape() {
    return mShape->getHavokShape();
}

const hkpShape* CharacterPrismShape::getHavokShape() const {
    return mShape->getHavokShapeConst();
}

const hkpShape* CharacterPrismShape::updateHavokShape() {
    return mShape->updateHavokShape();
}

void CharacterPrismShape::setScale(float scale) {
    mShape->setScale(scale);
}

}  // namespace ksys::phys
