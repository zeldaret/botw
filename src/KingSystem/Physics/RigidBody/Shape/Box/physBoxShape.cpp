#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Havok/Physics2012/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.h>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

BoxShape* BoxShape::make(const BoxShapeParam& param, sead::Heap* heap) {
    hkpBoxShape* box = nullptr;
    if (auto* storage = util::allocStorage<hkpBoxShape>(heap)) {
        const auto radius = param.convex_radius;
        const hkVector4f half_extents{sead::Mathf::max(param.extents.x / 2 - radius, 0.001),
                                      sead::Mathf::max(param.extents.y / 2 - radius, 0.001),
                                      sead::Mathf::max(param.extents.z / 2 - radius, 0.001)};
        box = new (storage) hkpBoxShape(half_extents, radius);
    }

    hkpConvexTransformShape* transform_shape = nullptr;
    if (auto* storage = util::allocStorage<hkpConvexTransformShape>(heap)) {
        sead::Quatf rotation;
        rotation.setRPY(param.rotate.x, param.rotate.y, param.rotate.z);
        hkQsTransformf transform{toHkVec4(param.translate), toHkQuat(rotation)};
        transform_shape = new (storage) hkpConvexTransformShape(box, transform);
    }

    if (!box || !transform_shape) {
        if (box)
            delete reinterpret_cast<u8*>(box);
        if (transform_shape)
            delete reinterpret_cast<u8*>(transform_shape);
        return nullptr;
    }

    return new (heap) BoxShape(param, box, transform_shape);
}

BoxShape* BoxShape::clone(sead::Heap* heap) const {
    BoxShapeParam param;
    param.extents = mExtents;
    param.translate = mTranslate;
    param.rotate = mRotate;
    auto* cloned = make(param, heap);
    cloned->setMaterialMask(mMaterialMask);
    return cloned;
}

BoxShape::BoxShape(const BoxShapeParam& param, hkpBoxShape* shape,
                   hkpConvexTransformShape* transform_shape)
    : mExtents(param.extents), mTranslate(param.translate), mRotate(param.rotate),
      mHavokShape(shape), mMaterialMask(param.common.getMaterialMask()),
      mTransformShape(transform_shape) {
    const bool no_transform =
        mTranslate == sead::Vector3f(0, 0, 0) && mRotate == sead::Vector3f(0, 0, 0);
    mFlags.change(Flag::HasTransform, !no_transform);

    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
}

BoxShape::~BoxShape() {
    util::deallocateObjectUnsafe(mHavokShape);
    util::deallocateObjectUnsafe(mTransformShape);
}

bool BoxShape::setExtents(const sead::Vector3f& extents) {
    if (mExtents == extents)
        return false;

    mExtents = extents;
    mFlags.set(Flag::Dirty);
    return true;
}

bool BoxShape::setTranslate(const sead::Vector3f& translate) {
    if (mTranslate == translate)
        return false;

    mTranslate = translate;

    const bool had_transform = mFlags.isOn(Flag::HasTransform);
    const bool no_transform =
        mTranslate == sead::Vector3f(0, 0, 0) && mRotate == sead::Vector3f(0, 0, 0);

    mFlags.change(Flag::HasTransform, !no_transform);
    mFlags.change(Flag::DirtyTransform, had_transform != !no_transform);
    mFlags.set(Flag::Dirty);

    return true;
}

void BoxShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;

    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());

    if (mTransformShape)
        mTransformShape->setUserData(mask.getRawData());
}

float BoxShape::getVolume() const {
    return mExtents.x * mExtents.y * mExtents.z;
}

hkpShape* BoxShape::getHavokShape() {
    if (mFlags.isOn(Flag::HasTransform))
        return mTransformShape;
    return mHavokShape;
}

const hkpShape* BoxShape::getHavokShape() const {
    if (mFlags.isOn(Flag::HasTransform))
        return mTransformShape;
    return mHavokShape;
}

const hkpShape* BoxShape::updateHavokShape() {
    if (mFlags.isOn(Flag::Dirty)) {
        {
            const auto radius = mHavokShape->getRadius();
            const sead::Vector3f half_extents{sead::Mathf::max(mExtents.x / 2 - radius, 0.001),
                                              sead::Mathf::max(mExtents.y / 2 - radius, 0.001),
                                              sead::Mathf::max(mExtents.z / 2 - radius, 0.001)};
            const auto ref_count = mHavokShape->getReferenceCount();
            mHavokShape = new (mHavokShape) hkpBoxShape(toHkVec4(half_extents), radius);
            mHavokShape->setReferenceCount(ref_count);
        }
        {
            sead::Quatf rotation;
            rotation.setRPY(mRotate.x, mRotate.y, mRotate.z);
            hkQsTransformf transform{toHkVec4(mTranslate), toHkQuat(rotation)};
            const auto ref_count = mTransformShape->getReferenceCount();
            mTransformShape = new (mTransformShape) hkpConvexTransformShape(mHavokShape, transform);
            mTransformShape->setReferenceCount(ref_count);
        }

        setMaterialMask(mMaterialMask);

        mFlags.reset(Flag::Dirty);
    }

    if (mFlags.isOn(Flag::DirtyTransform)) {
        mFlags.reset(Flag::DirtyTransform);
        return getHavokShapeConst();
    }

    return nullptr;
}

void BoxShape::setScale(float scale) {
    const auto scaled_extents = mExtents * scale;
    if (mExtents != scaled_extents) {
        mExtents = scaled_extents;
        mFlags.set(Flag::Dirty);
    }
    setTranslate(mTranslate * scale);
}

void BoxShape::getTranslate(sead::Vector3f* out, const hkTransformf& transform) const {
    hkVector4f translate;
    if (mFlags.isOn(Flag::HasTransform)) {
        hkVector4f transformed;
        transformed.setTransformedPos(transform, toHkVec4(mTranslate));
        translate = transformed;
    } else {
        translate = transform.getTranslation();
    }
    storeToVec3(out, translate);
}

}  // namespace ksys::phys
