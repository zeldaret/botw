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

static const sead::Vector3f& sOrigin = sead::Vector3f::zero;

CharacterPrismShape* CharacterPrismShape::make(const CharacterPrismShapeParam& param,
                                               sead::Heap* heap) {
    PolytopeShapeParam polytope_shape_param;
    polytope_shape_param.vertex_num = SHAPE_VERTEX_NUM;
    polytope_shape_param.common.material = param.common.material;
    polytope_shape_param.common.sub_material = param.common.sub_material;
    polytope_shape_param.common.floor_code = param.common.floor_code;
    polytope_shape_param.common.wall_code = param.common.wall_code;
    polytope_shape_param.common.item_code_disable_stick = param.common.item_code_disable_stick;

    auto* polytope_shape = PolytopeShape::make(polytope_shape_param, heap);

    /*
     * Set all vertices.
     */

    // Set first vertex
    polytope_shape->setVertex(0, sOrigin + param.offset);

    for (int i = 0, vertex_idx = 1; i < RING_VERTEX_NUM; i++, vertex_idx += 2) {
        float ring_x = param.radius * sin((float)i * (float)M_PI_4);
        float ring_z = param.radius * cos((float)i * (float)M_PI_4);

        // First ring
        polytope_shape->setVertex(vertex_idx, sead::Vector3f(ring_x, param.ring0_distance, ring_z) +
                                                  param.offset);

        // Second ring
        polytope_shape->setVertex(
            vertex_idx + 1, sead::Vector3f(ring_x, param.ring1_distance, ring_z) + param.offset);
    }

    // Set last vertex
    polytope_shape->setVertex(SHAPE_VERTEX_NUM - 1,
                              param.end_vertex_distance * sead::Vector3f::ey + param.offset);

    polytope_shape->updateHavokShape();

    /*
     * Set all vertices again, but move the bottom so that it lies at y=0.
     * This is undone if `CharacterPrismShape::setScale` is called.
     */

    // Get lowest vertex
    hkcdVertex supporting_vertex;
    polytope_shape->getVerticesShape()->getSupportingVertex(hkVector4f(0.0f, -1.0f, 0.0f),
                                                            supporting_vertex);
    // Get y-value of the lowest point of collision
    float min_vertex_y =
        supporting_vertex[1] + 0.0f - polytope_shape->getVerticesShape()->getRadius();

    // Set first vertex
    // Move to lie at y=0
    polytope_shape->setVertex(0, sOrigin + param.offset - min_vertex_y * sead::Vector3f::ey);

    for (int i = 0, vertex_idx = 1; i < RING_VERTEX_NUM; i++, vertex_idx += 2) {
        float ring_x = param.radius * sin((float)i * (float)M_PI_4);
        float ring_z = param.radius * cos((float)i * (float)M_PI_4);

        // First ring
        polytope_shape->setVertex(vertex_idx, sead::Vector3f(ring_x, param.ring0_distance, ring_z) +
                                                  param.offset - min_vertex_y * sead::Vector3f::ey);

        // Second ring
        polytope_shape->setVertex(
            vertex_idx + 1, sead::Vector3f(ring_x, param.ring1_distance, ring_z) + param.offset);
    }

    // Set last vertex
    polytope_shape->setVertex(SHAPE_VERTEX_NUM - 1,
                              param.end_vertex_distance * sead::Vector3f::ey + param.offset);

    polytope_shape->updateHavokShape();

    auto* shape = new (heap) CharacterPrismShape;
    shape->mShape = polytope_shape;
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

    auto scaled_offset = mOffset * scale;
    float scaled_end_vertex_distance = mEndVertexDistance * scale;
    float scaled_radius = mRadius * scale;
    float ring_y0 = mRing0Distance * scale;
    float ring_y1 = mRing1Distance * scale;

    // Set first vertex
    mShape->setVertex(0, sOrigin + scaled_offset);

    for (int i = 0, vertex_idx = 1; i < RING_VERTEX_NUM; i++, vertex_idx += 2) {
        // For some reason `sin` is used for x and `cos` is used for z.
        float ring_x = scaled_radius * sin((float)i * (float)M_PI_4);
        float ring_z = scaled_radius * cos((float)i * (float)M_PI_4);

        // First ring
        mShape->setVertex(vertex_idx, sead::Vector3f{ring_x, ring_y0, ring_z} + scaled_offset);

        // Second ring
        mShape->setVertex(vertex_idx + 1, sead::Vector3f{ring_x, ring_y1, ring_z} + scaled_offset);
    }

    // Set last vertex
    mShape->setVertex(SHAPE_VERTEX_NUM - 1,
                      scaled_end_vertex_distance * sead::Vector3f::ey + scaled_offset);

    mShape->setVolume(scale * scale * scale * volume);
}

CharacterPrismShape::~CharacterPrismShape() {
    if (mShape) {
        delete mShape;
        mShape = nullptr;
    }
}

}  // namespace ksys::phys
