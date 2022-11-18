#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
#include <Havok/Geometry/Internal/Types/hkcdVertex.h>
#include <Havok/Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

void CharacterPrismShape::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& CharacterPrismShape::getMaterialMask() const {
    return mShape->getMaterialMask();
}

static const sead::Vector3f& sOffset = sead::Vector3f::zero;

CharacterPrismShape* CharacterPrismShape::make(const CharacterPrismShapeParam& param,
                                               sead::Heap* heap) {
    PolytopeShapeParam polytopeShapeParam;
    polytopeShapeParam.vertex_num = SHAPE_VERTEX_NUM;
    polytopeShapeParam.common.material = param.common.material;
    polytopeShapeParam.common.sub_material = param.common.sub_material;
    polytopeShapeParam.common.floor_code = param.common.floor_code;
    polytopeShapeParam.common.wall_code = param.common.wall_code;
    polytopeShapeParam.common.item_code_disable_stick = param.common.item_code_disable_stick;

    auto* polytopeShape = PolytopeShape::make(polytopeShapeParam, heap);

    polytopeShape->setVertex(0, sOffset + param.offset);

    for (int i = 0, vertexIdx = 1; i < RING_VERTEX_NUM; i++, vertexIdx += 2) {
        float ringX = param.radius * sin((float)i * (float)M_PI_4);
        float ringZ = param.radius * cos((float)i * (float)M_PI_4);

        // First ring
        polytopeShape->setVertex(vertexIdx,
                                 sead::Vector3f(ringX, param.ring0_distance, ringZ) + param.offset);

        // Second ring
        polytopeShape->setVertex(vertexIdx + 1,
                                 sead::Vector3f(ringX, param.ring1_distance, ringZ) + param.offset);
    }

    polytopeShape->setVertex(SHAPE_VERTEX_NUM - 1,
                             param.end_vertex_distance * sead::Vector3f::ey + param.offset);

    polytopeShape->updateHavokShape();

    hkcdVertex supportingVertex;
    polytopeShape->getVerticesShape()->getSupportingVertex(hkVector4f(0.0f, -1.0f, 0.0f),
                                                           supportingVertex);

    float minVertexY = supportingVertex[1] + 0.0f - polytopeShape->getVerticesShape()->getRadius();
    polytopeShape->setVertex(0, sOffset + param.offset - minVertexY * sead::Vector3f::ey);

    for (int i = 0, vertexIdx = 1; i < RING_VERTEX_NUM; i++, vertexIdx += 2) {
        float ringX = param.radius * sin((float)i * (float)M_PI_4);
        float ringZ = param.radius * cos((float)i * (float)M_PI_4);

        // First ring
        polytopeShape->setVertex(vertexIdx, sead::Vector3f(ringX, param.ring0_distance, ringZ) +
                                                param.offset - minVertexY * sead::Vector3f::ey);

        // Second ring
        polytopeShape->setVertex(vertexIdx + 1,
                                 sead::Vector3f(ringX, param.ring1_distance, ringZ) + param.offset);
    }

    polytopeShape->setVertex(SHAPE_VERTEX_NUM - 1,
                             param.end_vertex_distance * sead::Vector3f::ey + param.offset);
    polytopeShape->updateHavokShape();

    auto* shape = new (heap) CharacterPrismShape;
    shape->mShape = polytopeShape;
    shape->mRadius = param.radius;
    shape->mRing0Distance = param.ring0_distance;
    shape->mRing1Distance = param.ring1_distance;
    shape->mEndVertexDistance = param.end_vertex_distance;
    shape->mOffset.e = param.offset.e;
    shape->mScale = 1.0f;
    return shape;
}

CharacterPrismShape* CharacterPrismShape::clone(sead::Heap* heap) const {
    CharacterPrismShapeParam param;
    param.radius = mRadius;
    param.end_vertex_distance = mEndVertexDistance;
    param.ring1_distance = mRing1Distance;
    param.ring0_distance = mRing0Distance;
    param.offset = mOffset;
    param.common.material = mShape->getMaterialMask().getMaterial();
    param.common.sub_material = mShape->getMaterialMask().getSubMaterialName();
    param.common.floor_code = mShape->getMaterialMask().getFloorCode();
    param.common.wall_code = mShape->getMaterialMask().getWallCode();
    auto data = mShape->getMaterialMask().getData();
    param.common.item_code_disable_stick = data.getCustomFlag(MaterialMaskData::CustomFlag::_0);
    return make(param, heap);
}

float CharacterPrismShape::getVolume() const {
    return mShape->getVolume();
}

hkpShape* CharacterPrismShape::getHavokShape() {
    // For some reason, this non-const function is calling the const function `getHavokShapeConst`.
    return const_cast<hkpShape*>(mShape->getHavokShapeConst());
}

const hkpShape* CharacterPrismShape::getHavokShape() const {
    return mShape->getHavokShapeConst();
}

const hkpShape* CharacterPrismShape::updateHavokShape() {
    return mShape->updateHavokShape();
}

void CharacterPrismShape::setScale(float scale) {
    // `mScale` is scaled relatively by `scale`, but vertices are scaled absolutely.
    // Using `CharacterPrismShape::setScale` more than once will put `mScale` out of sync with
    // the actual scale.
    mScale *= scale;

    float volume = getVolume();

    auto scaledOffset = mOffset * scale;
    float endVertexDistance = mEndVertexDistance * scale;
    float scaledRadius = mRadius * scale;
    float ringY0 = mRing0Distance * scale;
    float ringY1 = mRing1Distance * scale;

    // Set first vertex
    mShape->setVertex(0, scaledOffset + sead::Vector3f::zero);

    for (int i = 0, vertexIdx = 1; i < RING_VERTEX_NUM; i++, vertexIdx += 2) {
        // For some reason `sin` is used for x and `cos` is used for z.
        float ringX = scaledRadius * sin((float)i * (float)M_PI_4);
        float ringZ = scaledRadius * cos((float)i * (float)M_PI_4);

        // First ring
        mShape->setVertex(vertexIdx, scaledOffset + sead::Vector3f{ringX, ringY0, ringZ});

        // Second ring
        mShape->setVertex(vertexIdx + 1, scaledOffset + sead::Vector3f{ringX, ringY1, ringZ});
    }

    // Set last vertex
    mShape->setVertex(SHAPE_VERTEX_NUM - 1, scaledOffset + endVertexDistance * sead::Vector3f::ey);

    mShape->setVolume(scale * scale * scale * volume);
}

CharacterPrismShape::~CharacterPrismShape() {
    if (mShape) {
        delete mShape;
        mShape = nullptr;
    }
}

}  // namespace ksys::phys
