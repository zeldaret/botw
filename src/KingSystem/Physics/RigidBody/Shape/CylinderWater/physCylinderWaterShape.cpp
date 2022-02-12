#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterShape.h"
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabbUtil.h>
#include <Havok/Common/Base/Types/Geometry/Sphere/hkSphere.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/Query/hkpRayHitCollector.h>
#include <Havok/Physics2012/Collide/Shape/HeightField/hkpHeightFieldShape.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

static void addAabb(const hkTransform localToWorld, const hkVector4& halfExtents, hkAabb& aabbOut) {
    hkVector4f x, y, z;
    x.setMul(halfExtents.getComponent<0>(), localToWorld.getRotation().getColumn<0>());
    y.setMul(halfExtents.getComponent<1>(), localToWorld.getRotation().getColumn<1>());
    z.setMul(halfExtents.getComponent<2>(), localToWorld.getRotation().getColumn<2>());

    hkVector4f max;
    max.setAdd(x, y);
    max.add(z);
    aabbOut.m_min.add(max);
    aabbOut.m_max.add(max);
}

class alignas(16) HavokCylinderWaterShape : public hkpHeightFieldShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(HavokCylinderWaterShape)

    HavokCylinderWaterShape() : hkpHeightFieldShape(hkcdShapeType::HEIGHT_FIELD) {}

    void setRadius(float radius) { m_radius = radius; }

    void getAabb(const hkTransform& localToWorld, hkReal tolerance,
                 hkAabb& aabbOut) const override {
        hkVector4 half_extents(m_height / 2, m_radius / 2, m_radius / 2);
        hkAabbUtil::calcAabb(localToWorld, half_extents, tolerance, aabbOut);

        hkVector4 half_extents2(0, -m_radius / 2, m_radius / 2);
        addAabb(localToWorld, half_extents2, aabbOut);
    }

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& output) const override {
        // FIXME: implement
        return false;
    }

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override {
        hkpShapeRayCastOutput output;
        output.m_hitFraction = collector.m_earlyOutHitFraction;
        if (castRay(input, output)) {
            output.m_normal._setRotatedDir(cdBody.getTransform().getRotation(), output.m_normal);
            collector.addRayHit(cdBody, output);
        }
    }

    void collideSpheres(const CollideSpheresInput& input,
                        SphereCollisionOutput* outputArray) const override {
        auto* sphere = input.m_spheres;
        const hkSphere dummy({0, 1, 0}, hkSimdReal::getConstant<HK_QUADREAL_MAX>());

        for (int i = input.m_numSpheres - 1; i >= 0; --i) {
            hkSphere out = dummy;

            // FIXME: implement the rest of this function

            *outputArray = out.getPositionAndRadius();
            ++sphere;
            ++outputArray;
        }
    }

    void castSphere(const hkpSphereCastInput& input, const hkpCdBody& cdBody,
                    hkpRayHitCollector& collector) const override {}

    float m_height = 1.0;
    float m_radius = 1.0;
};

CylinderWaterShape* CylinderWaterShape::make(const CylinderShapeParam& param, sead::Heap* heap) {
    void* storage = util::allocStorage<HavokCylinderWaterShape>(heap);
    if (!storage)
        return nullptr;

    auto* hk_shape = new (storage) HavokCylinderWaterShape;
    return new (heap) CylinderWaterShape(param, hk_shape);
}

CylinderWaterShape::CylinderWaterShape(const CylinderShapeParam& param,
                                       HavokCylinderWaterShape* shape)
    : mMaterialMask(param.common.getMaterialMask()), mHavokShape(shape) {
    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
    mHavokShape->setRadius(param.radius);
    mHavokShape->m_height = param.vertex_a.x;
}

CylinderWaterShape::~CylinderWaterShape() {
    util::deallocateObjectUnsafe(mHavokShape);
}

void CylinderWaterShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;
    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());
}

bool CylinderWaterShape::setRadius(float radius) {
    if (!mHavokShape)
        return false;

    if (mHavokShape->m_radius == radius)
        return false;

    mHavokShape->m_radius = radius;
    mFlags.set(Flag::Dirty);
    return true;
}

bool CylinderWaterShape::setHeight(float height) {
    if (mHavokShape->m_height == height)
        return false;

    mHavokShape->m_height = height;
    mFlags.set(Flag::Dirty);
    return true;
}

CylinderWaterShape* CylinderWaterShape::clone(sead::Heap* heap) const {
    CylinderShapeParam param;
    param.radius = getRadius();
    param.vertex_a.x = getHeight();
    auto* cloned = make(param, heap);
    cloned->setMaterialMask(mMaterialMask);
    return cloned;
}

float CylinderWaterShape::getRadius() const {
    return mHavokShape->m_radius;
}

float CylinderWaterShape::getHeight() const {
    return mHavokShape->m_height;
}

float CylinderWaterShape::getVolume() const {
    return getHeight() * (sead::Mathf::piHalf() * getRadius() * getRadius());
}

hkpShape* CylinderWaterShape::getHavokShape() {
    return mHavokShape;
}

const hkpShape* CylinderWaterShape::getHavokShape() const {
    return mHavokShape;
}

const hkpShape* CylinderWaterShape::updateHavokShape() {
    if (mFlags.isOn(Flag::Dirty)) {
        // Nothing to do.
        mFlags.reset(Flag::Dirty);
    }
    return nullptr;
}

void CylinderWaterShape::setScale(float scale) {
    setRadius(getRadius() * scale);
    setHeight(getHeight() * scale);
}

}  // namespace ksys::phys
