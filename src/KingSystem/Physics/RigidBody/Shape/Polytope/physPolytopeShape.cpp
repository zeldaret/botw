#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include <Havok/Common/Base/Types/Geometry/hkStridedVertices.h>
#include <Havok/Physics2012/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include <Havok/Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/physHeapUtil.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

PolytopeShape* PolytopeShape::make(const PolytopeShapeParam& param, sead::Heap* heap) {
    auto* shape = new (heap) PolytopeShape(param);

    if (!shape->init(param, heap)) {
        delete shape;
        return nullptr;
    }

    return shape;
}

PolytopeShape* PolytopeShape::clone(sead::Heap* heap) const {
    PolytopeShapeParam param;
    param.vertex_num = u16(mVertices.size());

    auto* cloned = make(param, heap);

    for (int i = 0; i < int(param.vertex_num); ++i) {
        cloned->setVertex(i, getVertex(i));
    }
    cloned->setNumVertices(getNumVertices());
    cloned->updateHavokShape();
    cloned->setMaterialMask(getMaterialMask());
    return cloned;
}

bool PolytopeShape::setVertex(int vertex_idx, const sead::Vector3f& vertex) {
    if (mFlags.isOn(Flag::HasCustomScale)) {
        mScale = 1.0;
        mFlags.reset(Flag::HasCustomScale);
        mFlags.set(Flag::_4);
        mFlags.set(Flag::_10);
    }

    if (vertex != mVertices[vertex_idx]) {
        mVertices[vertex_idx] = vertex;
        mFlags.set(Flag::_1 | Flag::InvalidVolume);
        mVolume = -1.0;
        return true;
    }

    return false;
}

void PolytopeShape::setNumVertices(u16 num) {
    if (mNumVertices == num)
        return;

    mNumVertices = num;
    mVolume = -1.0;
    mFlags.set(Flag::_1 | Flag::InvalidVolume);
}

PolytopeShape::PolytopeShape(const PolytopeShapeParam& param)
    : mMaterialMask(param.common.getMaterialMask()), mNumVertices(param.vertex_num) {
    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
}

PolytopeShape::~PolytopeShape() {
    deleteRefCountedHavokObject(mHavokShape);
    util::deallocateObjectUnsafe(mTransformShape);
    mVertices.freeBuffer();
}

hkpShape* PolytopeShape::getHavokShape() {
    if (mFlags.isOn(Flag::HasCustomScale))
        return mTransformShape;
    return mHavokShape;
}

const hkpShape* PolytopeShape::getHavokShape() const {
    if (mFlags.isOn(Flag::HasCustomScale))
        return mTransformShape;
    return mHavokShape;
}

const hkpShape* PolytopeShape::updateHavokShape() {
    bool return_new_shape = false;

    if (mFlags.isOn(Flag::_1)) {
        auto lock = sead::makeScopedLock(mCS);

        mHavokShape->setConnectivity(nullptr, false);

        hkStridedVertices vertices;
        vertices.set(mVertices.getBufferPtr(), mNumVertices);
        if (auto* shape = new hkpConvexVerticesShape(vertices)) {
            // TODO

            for (int i = 0, n = shape->getReferenceCount(); i < n; ++i)
                shape->removeReference();
        }

        if (mFlags.isOn(Flag::InvalidVolume)) {
            if (auto* connectivity = mHavokShape->getConnectivity()) {
                // TODO: recalculate volume
                mVolume = {};
            } else {
                // TODO
            }
            mFlags.reset(Flag::InvalidVolume);
        }

        mFlags.reset(Flag::_1);
    }

    if (mFlags.isOn(Flag::_4)) {
        auto lock = sead::makeScopedLock(mCS);

        hkQsTransform transform;
        transform.setIdentity();
        transform.m_scale.setAll(mScale);
        const auto ref_count = mTransformShape->getReferenceCount();
        mTransformShape = new (mTransformShape) hkpConvexTransformShape(
            mHavokShape, transform, hkpShapeContainer::REFERENCE_POLICY_IGNORE);
        mTransformShape->setReferenceCount(ref_count);

        mFlags.reset(Flag::_4);
    }

    setMaterialMask(mMaterialMask);

    if (mFlags.isOn(Flag::_10)) {
        mFlags.reset(Flag::_10);
    } else if (!return_new_shape) {
        return nullptr;
    }

    return getHavokShapeConst();
}

void PolytopeShape::setScale(float scale) {
    const bool invalid_volume = mFlags.isOn(Flag::InvalidVolume);
    const float volume = mVolume;

    mScale *= scale;
    mFlags.set(Flag::_4);
    if (sead::Mathf::equalsEpsilon(mScale, 1.0)) {
        mScale = 1.0;
    }

    // Rescale all vertices.
    for (int i = 0, n = int(mNumVertices); i < n; ++i) {
        mVertices[i] = scale * getVertex(i);
    }

    const bool had_custom_scale = mFlags.isOn(Flag::HasCustomScale);
    const bool has_custom_scale = mScale != 1.0;
    mFlags.change(Flag::HasCustomScale, has_custom_scale);
    mFlags.change(Flag::_10, had_custom_scale != has_custom_scale);

    if (!invalid_volume) {
        setVolume(scale * scale * scale * volume);
    }
}

void PolytopeShape::setVolume(float volume) {
    mVolume = volume;
    mFlags.reset(Flag::InvalidVolume);
}

float PolytopeShape::getVolume() const {
    return mVolume;
}

void PolytopeShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;

    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());

    if (mTransformShape)
        mTransformShape->setUserData(mask.getRawData());
}

bool PolytopeShape::init(const PolytopeShapeParam& param, sead::Heap* heap) {
    mVertices.allocBufferAssert(param.vertex_num, heap);
    mNumVertices = param.vertex_num;

    for (int i = 0; i < int(param.vertex_num); ++i) {
        sead::Mathf::sinCosIdx(&mVertices[i].y, &mVertices[i].z,
                               (sead::Mathu::maxNumber() / mNumVertices) * i);
        mVertices[i].x = static_cast<float>(i % 2);
    }

    // Alloc the vertices shape.
    hkStridedVertices vertices;
    vertices.set(mVertices.getBufferPtr(), mNumVertices);
    mHavokShape = new hkpConvexVerticesShape(vertices);
    if (!mHavokShape) {
        return false;
    }

    // Alloc the transform shape.
    if (auto* storage = util::allocStorage<hkpConvexTransformShape>(heap)) {
        mTransformShape =
            new (storage) hkpConvexTransformShape(mHavokShape, hkQsTransform::IdentityInitializer(),
                                                  hkpShapeContainer::REFERENCE_POLICY_IGNORE);
    }

    setMaterialMask(mMaterialMask);
    return true;
}

}  // namespace ksys::phys
