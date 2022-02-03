#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterShape.h"
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Common/Base/Types/Geometry/Sphere/hkSphere.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/Plane/hkpPlaneShape.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

class HavokPlaneShape : public hkpPlaneShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(HavokPlaneShape)

    HavokPlaneShape(const hkVector4& plane, const hkAabb& aabb) : hkpPlaneShape(plane, aabb) {}

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override {
        const auto dot_from = getPlane().dot4xyz1(input.m_from);
        const auto dot_to = getPlane().dot4xyz1(input.m_to);
        if (dot_from.isGreaterZero() && dot_to.isGreaterZero())
            return false;

        hkSimdReal hit_fraction;
        if (dot_from.isLessEqualZero())
            hit_fraction = 0;
        else
            hit_fraction = dot_from * (dot_from - dot_to).reciprocal();

        if (!hkSimdReal(results.m_hitFraction).isGreater(hit_fraction))
            return false;

        hkVector4f position;
        position.setInterpolate(input.m_from, input.m_to, hit_fraction.val());

        hkVector4f rel_pos;
        rel_pos.setSub(position, getAabbCenter());
        rel_pos.setAbs(rel_pos);
        rel_pos.sub(0.0001);

        if (!getAabbHalfExtents().greaterEqual(rel_pos).allAreSet<hkVector4fComparison::MASK_XYZ>())
            return false;

        results.m_hitFraction = hit_fraction;
        results.m_normal = getPlane();
        results.setKey(HK_INVALID_SHAPE_KEY);
        return true;
    }

    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override {
        auto* sphere = input.m_spheres;
        for (int i = input.m_numSpheres - 1; i >= 0; --i) {
            const auto r =
                getPlane().dot4xyz1(sphere->getPositionAndRadius()) - sphere->getRadiusSimdReal();

            auto w = hkSimdReal::getConstant<HK_QUADREAL_MAX>();

            if (r < input.m_tolerance) {
                const auto r_ = sphere->getRadiusSimdReal() + hkSimdReal(input.m_tolerance);

                hkVector4f half_extents;
                half_extents.setAdd(getAabbHalfExtents(), r_);

                hkVector4f rel_pos;
                rel_pos.setSub(sphere->getPositionAndRadius(), getAabbCenter());
                rel_pos.setAbs(rel_pos);

                if (!rel_pos.greater(half_extents).anyIsSet(hkVector4fComparison::MASK_XYZ))
                    w = r;
            }

            outputArray->setXYZ_W(getPlane(), w);
            ++sphere;
            ++outputArray;
        }
    }
};

BoxWaterShape* BoxWaterShape::make(const BoxShapeParam& param, sead::Heap* heap) {
    void* storage = util::allocStorage<HavokPlaneShape>(heap);
    if (!storage)
        return nullptr;

    hkVector4f plane(0, 1, 0);
    plane.setW(param.translate.y + param.extents.y / 2);

    hkAabb aabb;
    aabb.m_min.setSub(toHkVec4(param.translate), toHkVec4(param.extents / 2));
    aabb.m_max.setAdd(toHkVec4(param.translate), toHkVec4(param.extents / 2));

    auto* hk_shape = new (storage) HavokPlaneShape(plane, aabb);
    return new (heap) BoxWaterShape(param, hk_shape);
}

BoxWaterShape* BoxWaterShape::clone(sead::Heap* heap) const {
    BoxShapeParam param;
    param.extents = mExtents;
    param.translate = mTranslate;
    param.rotate = mRotate;

    auto* cloned = make(param, heap);
    cloned->setMaterialMask(mMaterialMask);
    return cloned;
}

BoxWaterShape::BoxWaterShape(const BoxShapeParam& param, hkpPlaneShape* hk_shape)
    : mExtents(param.extents), mTranslate(param.translate), mRotate(param.rotate),
      mHavokShape(hk_shape), mMaterialMask(param.common.getMaterialMask()) {
    mFlags.change(Flag::IsWater, param.common.material == Material::Water);

    const bool no_transform =
        mTranslate == sead::Vector3f(0, 0, 0) && mRotate == sead::Vector3f(0, 0, 0);
    mFlags.change(Flag::HasTransform, !no_transform);

    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
}

BoxWaterShape::~BoxWaterShape() {
    util::deallocateObjectUnsafe(mHavokShape);
}

void BoxWaterShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;

    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());
}

bool BoxWaterShape::setExtents(const sead::Vector3f& extents) {
    if (mExtents == extents)
        return false;

    mExtents = extents;
    mFlags.set(Flag::Dirty);
    return true;
}

bool BoxWaterShape::setTranslate(const sead::Vector3f& translate) {
    if (mTranslate == translate)
        return false;

    mTranslate = translate;

    mFlags.change(Flag::HasTransform, !hasNoTransform());
    mFlags.set(Flag::Dirty);
    return true;
}

float BoxWaterShape::getVolume() const {
    return mExtents.x * mExtents.y * mExtents.z;
}

hkpShape* BoxWaterShape::getHavokShape() {
    return mHavokShape;
}

const hkpShape* BoxWaterShape::getHavokShape() const {
    return mHavokShape;
}

const hkpShape* BoxWaterShape::updateHavokShape() {
    if (!mFlags.isOn(Flag::Dirty))
        return nullptr;

    const auto ref_count = mHavokShape->getReferenceCount();

    hkVector4f plane(0, 1, 0);
    plane.setW(mTranslate.y + mExtents.y / 2);

    hkAabb aabb;
    aabb.m_min.setSub(toHkVec4(mTranslate), toHkVec4(mExtents / 2));
    aabb.m_max.setAdd(toHkVec4(mTranslate), toHkVec4(mExtents / 2));

    mHavokShape = new (mHavokShape) HavokPlaneShape(plane, aabb);
    mHavokShape->setReferenceCount(ref_count);

    setMaterialMask(mMaterialMask);

    mFlags.reset(Flag::Dirty);
    return nullptr;
}

void BoxWaterShape::setScale(float scale) {
    setExtents(mExtents * scale);
    setTranslate(mTranslate * scale);
}

}  // namespace ksys::phys
