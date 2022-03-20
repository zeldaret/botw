#include "KingSystem/Physics/RigidBody/physRigidBodyFromResource.h"
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpPhysicsSystem.h>
#include <Havok/Physics2012/Utilities/Dynamics/ScaleSystem/hkpSystemScalingUtility.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

static const char* getRigidBodyResourceName(const hkpRigidBody* hk_body) {
    if (const char* name = hk_body->getName())
        return name;

    return "RigidBodyFromResource";
}

RigidBodyFromResource::RigidBodyFromResource(float volume, hkpRigidBody* hk_body,
                                             ContactLayerType layer_type, sead::Heap* heap,
                                             RigidBody::Type type)
    : RigidBody(type, layer_type, hk_body, getRigidBodyResourceName(hk_body), heap, true),
      mShape(hk_body->getCollidable()->getShape()), mVolume(volume) {}

RigidBodyFromResource::~RigidBodyFromResource() = default;

bool RigidBodyFromResource::init(const RigidBodyInstanceParam& param, sead::Heap* heap) {
    if (!initMotionAccessor(param, heap, true))
        return false;

    updateCollidableQualityType(param.toi);
    getHkBody()->getCollidableRw()->setMotionState(getHkBody()->getMotion()->getMotionState());

    if (auto* shape = getHkBody()->getCollidable()->getShape()) {
        hkVector4 extent_out;
        getHkBody()->updateCachedShapeInfo(shape, extent_out);
    }

    return true;
}

bool RigidBodyFromResource::isBvTreeOrStaticCompound() const {
    switch (mShape->getType()) {
    case hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_BV_TREE:
    case hkcdShapeType::MOPP:
    case hkcdShapeType::STATIC_COMPOUND:
    case hkcdShapeType::BV_COMPRESSED_MESH:
    case hkcdShapeType::BV_TREE:
        return true;
    default:
        return false;
    }
}

bool RigidBodyFromResource::isMaterial(Material material) const {
    if (isBvTreeOrStaticCompound())
        return false;

    bool found_child_shape_with_material = false;
    if (auto* container = mShape->getContainer()) {
        for (auto key = container->getFirstKey(); key != HK_INVALID_SHAPE_KEY;
             key = container->getNextKey(key)) {
            hkpShapeBuffer buffer;
            auto* shape = container->getChildShape(key, buffer);
            if (!shape)
                return false;

            MaterialMask shape_material{shape->getUserData()};
            if (int(shape_material.getMaterial()) == material) {
                found_child_shape_with_material = true;
                break;
            }
        }
    } else {
        MaterialMask shape_material{mShape->getUserData()};
        if (int(shape_material.getMaterial()) == material)
            return true;
    }

    return found_child_shape_with_material;
}

u32 RigidBodyFromResource::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                             const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask;
    auto* collidable = getHkBody()->getCollidable();
    if (unk != nullptr) {
        return getCollisionFilterInfoFromCollidable(masks, &masks->collision_filter_info,
                                                    *collidable, unk);
    }
    masks->material_mask = collidable->getShape()->getUserData();
    masks->collision_filter_info = collidable->getCollisionFilterInfo();
    return 0;
}

float RigidBodyFromResource::updateScale_(float scale, float old_scale) {
    if (getHkBody()->getCollidable()->getShape()->getType() == hkcdShapeType::BV_COMPRESSED_MESH) {
        static_cast<void>(getPosition());
        return old_scale;
    }

    mNewScale = scale;
    updateShape();
    return scale;
}

const hkpShape* RigidBodyFromResource::getNewHavokShape_() {
    if (sead::Mathf::equalsEpsilon(mCurrentScale, mNewScale))
        return nullptr;

    const float ratio = mNewScale / mCurrentScale;

    mVolume = ratio * ratio * ratio * mVolume;

    const hkTransformf saved_transform = getHkBody()->getTransform();
    hkTransformf identity;
    identity.setIdentity();
    getHkBody()->setTransform(identity);

    // Actually scale it now.
    // XXX: hkpSystemScalingUtility is not supposed to be used at runtime.
    hkpPhysicsSystem system;
    system.addRigidBody(getHkBody());
    hkpSystemScalingUtility::scaleSystem(&system, ratio);
    getHkBody()->setTransform(saved_transform);

    if (getHkBody()->getMass() > 0) {
        setMass(getHkBody()->getMass());
        setCenterOfMassInLocal(toVec3(getHkBody()->getCenterOfMassLocal()));

        hkMatrix3 inertia;
        getHkBody()->getInertiaLocal(inertia);
        setInertiaLocal({inertia.get<0, 0>(), inertia.get<1, 1>(), inertia.get<2, 2>()});
    }

    mCurrentScale = mNewScale;
    return nullptr;
}

float RigidBodyFromResource::getVolume() {
    return mVolume;
}

}  // namespace ksys::phys
