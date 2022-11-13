#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
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

// NON_MATCHING
CharacterPrismShape* CharacterPrismShape::make(const CharacterPrismShapeParam& param,
                                               sead::Heap* heap) {
    PolytopeShapeParam polytopeShapeParam;
    polytopeShapeParam.vertex_num = 18;
    polytopeShapeParam.common = param.common;
    auto* polytopeShape = PolytopeShape::make(polytopeShapeParam, heap);
    auto vertex = sead::Vector3f::zero + param.offset;
    auto position = -1.0f * sead::Vector3f::ey;
    polytopeShape->setVertex(0, vertex);
    float pi_4 = M_PI_4;

    for (int i = 0, vertexIdx = 1; i < 8; i++, vertexIdx += 2) {
        float ringX = param.radius * sin(static_cast<float>(i) * pi_4);
        float ringZ = param.radius * cos(static_cast<float>(i) * pi_4);
        // First ring
        vertex = sead::Vector3f(ringX, param.ring0_distance, ringZ) + param.offset;
        polytopeShape->setVertex(vertexIdx, vertex);
        // Second ring
        vertex = sead::Vector3f(ringX, param.ring1_distance, ringZ) + param.offset;
        polytopeShape->setVertex(vertexIdx + 1, vertex);
    }

    vertex = sead::Vector3f::ey + param.offset;
    polytopeShape->setVertex(17, vertex);
    polytopeShape->updateHavokShape();

    auto* havokShape = (hkpConvexShape*)polytopeShape->getHavokShape();

    havokShape->getSupportingVertex(toHkVec4(position), (hkcdVertex&)vertex);

    float upperRingY = vertex.y - havokShape->getRadius();
    position = vertex - upperRingY * sead::Vector3f::ey;
    polytopeShape->setVertex(0, position);

    for (int i = 0, vertexIdx = 1; i < 8; i++, vertexIdx += 2) {
        float ringX = param.radius * sin(static_cast<float>(i) * pi_4);
        float ringZ = param.radius * cos(static_cast<float>(i) * pi_4);
        vertex = sead::Vector3f(ringX, param.ring0_distance, ringZ) + param.offset;
        polytopeShape->setVertex(vertexIdx, vertex);
        vertex = sead::Vector3f(ringX, param.ring1_distance, ringZ) + param.offset;
        polytopeShape->setVertex(vertexIdx + 1, vertex);
    }

    vertex = param.end_vertex_distance * sead::Vector3f::ey + param.offset;
    polytopeShape->setVertex(17, vertex);
    polytopeShape->updateHavokShape();

    auto* shape = new (heap) CharacterPrismShape();
    shape->mShape = polytopeShape;
    shape->mRadius = param.radius;
    shape->mRing0Distance = param.ring0_distance;
    shape->mRing1Distance = param.ring1_distance;
    shape->mEndVertexDistance = param.end_vertex_distance;
    shape->mOffset = param.offset;
    shape->mScale = 1.0f;
    return shape;
}

CharacterPrismShape* CharacterPrismShape::clone(sead::Heap* heap) const {
    CharacterPrismShapeParam param;
    auto* cloned = make(param, heap);
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

// NON_MATCHING
void CharacterPrismShape::setScale(float scale) {
    mScale *= scale;

    float volume = getVolume();

    float firstRingDistance = mRing0Distance;
    float secondRingDistance = mRing1Distance;
    float endVertexDistance = mEndVertexDistance;
    float scaledOffsetX = scale * mOffset.x;
    float scaledOffsetY = scale * mOffset.y;
    float scaledOffsetZ = scale * mOffset.z;
    float scaledRadius = scale * mRadius;

    // Set first vertex
    mShape->setVertex(0, {scaledOffsetX, scaledOffsetY, scaledOffsetZ});

    float ringY0 = scaledOffsetY + firstRingDistance * scale;
    float ringY1 = scaledOffsetY + secondRingDistance * scale;

    int vertexIdx = 1;
    for (int i = 0; i < 8; i++, vertexIdx += 2) {
        // For some reason `sin` is used for x and `cos` is used for z.
        float ringX = scaledOffsetX + scaledRadius * sin((float)i * (float)M_PI_4);
        float ringZ = scaledOffsetZ + scaledRadius * cos((float)i * (float)M_PI_4);

        // First ring
        mShape->setVertex(vertexIdx, {ringX, ringY0, ringZ});

        // Second ring
        mShape->setVertex(vertexIdx + 1, {ringX, ringY1, ringZ});
    }

    // Set last vertex
    mShape->setVertex(17, {
                              scaledOffsetX + endVertexDistance * scale * sead::Vector3f::ey.x,
                              scaledOffsetY + endVertexDistance * scale * sead::Vector3f::ey.y,
                              scaledOffsetZ + endVertexDistance * scale * sead::Vector3f::ey.z,
                          });

    mShape->setVolume(scale * scale * scale * volume);
}

}  // namespace ksys::phys
