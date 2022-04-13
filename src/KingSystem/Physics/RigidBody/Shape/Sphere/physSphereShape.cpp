#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "math/seadMathCalcCommon.h"

#include <Havok/Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Havok/Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>

namespace ksys::phys {

SphereShape* SphereShape::make(const SphereShapeParam& param, sead::Heap* heap) {
    hkpSphereShape* sphere = nullptr;
    if (auto* storage = heap->alloc(sizeof(hkpSphereShape), 0x10)) {
        sphere = new (storage) hkpSphereShape(param.radius);
    }

    hkpConvexTranslateShape* translate_shape = nullptr;
    if (auto* storage = util::allocStorage<hkpConvexTranslateShape>(heap)) {
        translate_shape = new (storage) hkpConvexTranslateShape(sphere, toHkVec4(param.translate));

        if (sphere != nullptr) {
            return new (heap) SphereShape(param, sphere, translate_shape);
        }
    }

    if (sphere) {
        delete reinterpret_cast<u8*>(sphere);
    } else if (translate_shape) {
        delete reinterpret_cast<u8*>(translate_shape);
    }

    return nullptr;
}

SphereShape* SphereShape::clone(sead::Heap* heap) const {
    SphereShapeParam param;

    param.radius = mRadius;
    param.translate = mTranslate;

    auto* cloned = make(param, heap);
    cloned->setMaterialMask(mMaterialMask);
    return cloned;
}

SphereShape::SphereShape(const SphereShapeParam& param, hkpSphereShape* shape,
                         hkpConvexTranslateShape* translate_shape)
    : mRadius(param.radius), mHavokShape(shape), mTranslate(param.translate),
      mMaterialMask(param.common.getMaterialMask()), mTranslateShape(translate_shape) {
    const bool no_transform = mTranslate == sead::Vector3f(0, 0, 0);
    mFlags.change(Flag::HasTransform, !no_transform);

    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
}

SphereShape::~SphereShape() {
    util::deallocateObjectUnsafe(mHavokShape);
    util::deallocateObjectUnsafe(mTranslateShape);
}

void SphereShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;

    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());

    if (mTranslateShape)
        mTranslateShape->setUserData(mask.getRawData());
}

float SphereShape::getVolume() const {
    return 4 / 3 * sead::Mathf::pi() * mRadius * mRadius * mRadius;
}

hkpShape* SphereShape::getHavokShape() {
    if (mFlags.isOn(Flag::HasTransform))
        return mTranslateShape;

    return mHavokShape;
};

const hkpShape* SphereShape::getHavokShape() const {
    if (mFlags.isOn(Flag::HasTransform))
        return mTranslateShape;
    return mHavokShape;
};

const hkpShape* SphereShape::updateHavokShape() {
    if (mFlags.isOn(Flag::Dirty)) {
        {
            const auto ref_count = mHavokShape->getReferenceCount();
            mHavokShape = new (mHavokShape) hkpSphereShape(mRadius);
            mHavokShape->setReferenceCount(ref_count);
        }
        {
            const auto ref_count = mTranslateShape->getReferenceCount();
            mTranslateShape =
                new (mTranslateShape) hkpConvexTranslateShape(mHavokShape, toHkVec4(mTranslate));
            mTranslateShape->setReferenceCount(ref_count);
        }

        setMaterialMask(mMaterialMask);
        mFlags.reset(Flag::Dirty);
    }

    if (mFlags.isOn(Flag::DirtyTransform)) {
        mFlags.reset(Flag::DirtyTransform);
        return getHavokShapeConst();
    }

    return nullptr;
};

bool SphereShape::setRadius(float radius) {
    if (radius == mRadius || radius <= 0.0f) {
        return false;
    }

    mRadius = radius;
    mFlags.set(Flag::Dirty);
    return true;
}

void SphereShape::setScale(float scale) {
    setRadius(mRadius * scale);
    setTranslate(mTranslate * scale);
}

bool SphereShape::setTranslate(const sead::Vector3f& translate) {
    if (mTranslate == translate)
        return false;

    mTranslate = translate;

    const bool had_transform = mFlags.isOn(Flag::HasTransform);
    const bool no_transform = translate == sead::Vector3f(0, 0, 0);

    mFlags.change(Flag::HasTransform, !no_transform);
    mFlags.change(Flag::DirtyTransform, had_transform != !no_transform);
    mFlags.set(Flag::Dirty);

    return true;
}

void SphereShape::getTranslate(sead::Vector3f* out, const hkTransformf& transform) const {
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