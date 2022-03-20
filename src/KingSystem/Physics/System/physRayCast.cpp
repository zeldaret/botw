#include "KingSystem/Physics/System/physRayCast.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Havok/Physics2012/Collide/Query/hkpRayHitCollector.h>
#include <Havok/Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Havok/Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <Havok/Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include <Havok/Physics2012/Utilities/Collide/ShapeUtils/ShapeKeyPath/hkpShapeKeyPath.h>
#include <prim/seadScopeGuard.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include "KingSystem/Physics/System/physEntityContactListener.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physPhantom.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physLayerMaskBuilder.h"

namespace ksys::phys {

class RayHitCollector : public hkpRayHitCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(RayHitCollector)

    RayHitCollector(hkpWorldRayCastOutput* output, ContactLayerType layer_type,
                    const sead::PtrArray<SystemGroupHandler>* ignored_groups,
                    GroundHit ignored_ground_hit)
        : mOutput(output), mLayerType(layer_type), mIgnoredGroups(ignored_groups),
          mIgnoredGroundHit(ignored_ground_hit) {}

    ~RayHitCollector() override;

    void addRayHit(const hkpCdBody& cdBody, const hkpShapeRayCastCollectorOutput& hitInfo) override;

protected:
    bool isIgnoredGroup(const hkpCdBody& cdBody,
                        const hkpShapeRayCastCollectorOutput& hitInfo) const;

    bool isIgnoredGroundHit(const hkpCdBody& cdBody,
                            const hkpShapeRayCastCollectorOutput& hitInfo) const;

    hkpWorldRayCastOutput* mOutput;
    ContactLayerType mLayerType;
    const sead::PtrArray<SystemGroupHandler>* mIgnoredGroups;
    GroundHit mIgnoredGroundHit;
};

class NormalCheckingRayHitCollector : public RayHitCollector {
public:
    HK_DECLARE_CLASS_ALLOCATOR(NormalCheckingRayHitCollector)

    NormalCheckingRayHitCollector(hkpWorldRayCastOutput* output, const sead::Vector3f& ray_line,
                                  RayCast::NormalCheckingMode mode, ContactLayerType layer_type,
                                  const sead::PtrArray<SystemGroupHandler>* ignored_groups,
                                  GroundHit ignored_ground_hit)
        : RayHitCollector(output, layer_type, ignored_groups, ignored_ground_hit),
          mRayLine(&ray_line), mMode(mode) {}

    ~NormalCheckingRayHitCollector() override;

    void addRayHit(const hkpCdBody& cdBody, const hkpShapeRayCastCollectorOutput& hitInfo) override;

    bool checkNormal(const hkpCdBody& cdBody, const hkpShapeRayCastCollectorOutput& hitInfo) const;

private:
    const sead::Vector3f* mRayLine;
    RayCast::NormalCheckingMode mMode;
};

RayCast::RayCast(SystemGroupHandler* group_handler, GroundHit ground_hit)
    : mGroupHandler(group_handler), mGroundHit(ground_hit) {
    reset();
}

RayCast::~RayCast() = default;

// NON_MATCHING: reorderings
void RayCast::reset() {
    mTo = sead::Vector3f::zero;
    mFrom = sead::Vector3f::zero;
    mLayerMasks = {};
    mIgnoredGroups.clear();

    resetCastResult();
}

void RayCast::resetCastResult() {
    static_cast<void>(_98.load());

    mHasHit = false;
    mHitNormal = sead::Vector3f::zero;
    mHitFraction = -1.0;
    mHitCollidable = {};
    mHitShapeKey = {};
    mHasHitSpecifiedRigidBody = false;
    mHitBodyGroup = {};
    mHitMapObject = {};
    _70 = {};
}

static bool isLayerValid(ContactLayer layer, ContactLayerType type) {
    if (type == ContactLayerType::Entity) {
        if (layer > ContactLayer::EntityHitOnlyGround)
            return false;
    } else {
        if (layer > ContactLayer::SensorNoHit)
            return false;
    }

    return true;
}

void RayCast::enableLayer(ContactLayer layer) {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return;

    const auto mask = makeContactLayerMask(layer);
    getLayerMask(type).set(mask);
}

void RayCast::disableLayer(ContactLayer layer) {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return;

    getLayerMask(type).resetBit(getContactLayerBaseRelativeValue(layer));
}

void RayCast::setLayers(const LayerMaskBuilder& builder) {
    for (int i = 0; i < NumContactLayerTypes; ++i)
        mLayerMasks[i] = builder.getMasks()[i].layers;
}

bool RayCast::isLayerEnabled(ContactLayer layer) const {
    auto type = getContactLayerType(layer);
    if (!isLayerValid(layer, type))
        return false;

    return getLayerMask(type).isOnBit(getContactLayerBaseRelativeValue(layer));
}

void RayCast::setGroundHit(GroundHit ground_hit) {
    mGroundHit = ground_hit;
}

GroundHit RayCast::getGroundHit() const {
    return mGroundHit;
}

void RayCast::setIgnoredGroundHit(GroundHit ground_hit) {
    mIgnoredGroundHit = ground_hit;
}

void RayCast::set9A(bool value) {
    _9a = value;
}

void RayCast::setStart(const sead::Vector3f& start) {
    mFrom = start;
}

void RayCast::setEnd(const sead::Vector3f& end) {
    mTo = end;
}

void RayCast::setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end) {
    setStart(start);
    setEnd(end);
}

void RayCast::setStartAndDisplacement(const sead::Vector3f& start,
                                      const sead::Vector3f& displacement) {
    setStart(start);
    setEnd(start + displacement);
}

void RayCast::setStartAndDisplacementScaled(const sead::Vector3f& start,
                                            const sead::Vector3f& displacement,
                                            float displacement_scale) {
    setStart(start);
    setEnd(start + displacement * displacement_scale);
}

bool RayCast::addIgnoredGroup(SystemGroupHandler* group_handler) {
    if (mIgnoredGroups.size() == mIgnoredGroups.capacity() || group_handler == nullptr)
        return false;

    mIgnoredGroups.pushBack(group_handler);
    return true;
}

void RayCast::setRigidBody(RigidBody* body) {
    if (_70 != 1)
        mRigidBody = body;
}

void RayCast::fillCastInput(hkpWorldRayCastInput& input, ContactLayerType layer_type) {
    const u32 layer_mask = getLayerMask(layer_type);
    input.m_enableShapeCollectionFilter = true;
    input.m_filterInfo = getFilterInfo(layer_type, layer_mask);
    input.m_from = toHkVec4(mFrom);
    input.m_to = toHkVec4(mTo);
}

void RayCast::fillCastInput(hkpShapeRayCastInput& input, ContactLayerType layer_type) {
    input.m_filterInfo = getFilterInfo(layer_type, getLayerMask(layer_type));
}

u32 RayCast::getFilterInfo(ContactLayerType layer_type, u32 layer_mask) const {
    if (mGroupHandler != nullptr) {
        return mGroupHandler->makeQueryCollisionMask(layer_mask, mGroundHit, _9a);
    } else {
        auto* filter = System::instance()->getGroupFilter(layer_type);
        auto info = filter->makeQueryCollisionMask(layer_mask, mGroundHit, _9a);
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
        return info;
    }
}

void RayCast::preCast() {
    if (_70 == 1)
        resetCastResult();
    _98 = true;
}

bool RayCast::postCast(const hkpWorldRayCastOutput& output) {
    mHasHit = output.hasHit();
    if (mHasHit) {
        updateHitInformation(output);
        updateStaticCompoundObjectInfo(output);
    }
    _98 = false;
    _70 = 1;
    return mHasHit;
}

void RayCast::updateHitInformation(const hkpWorldRayCastOutput& output) {
    storeToVec3(&mHitNormal, output.m_normal);
    mHitFraction = output.m_hitFraction;
    mHitCollidable = output.m_rootCollidable;
    mHitShapeKey = output.m_shapeKeys[0];

    auto* hit_body = getRigidBody(*mHitCollidable);
    if (hit_body) {
        if (mRigidBody != nullptr && hit_body == mRigidBody)
            mHasHitSpecifiedRigidBody = true;

        onRigidBodyHit(hit_body);
        if (mRigidBodyHitCallback)
            mRigidBodyHitCallback->invoke(hit_body);
    }
}

bool RayCast::worldRayCast(ContactLayerType layer_type) {
    hkpWorldRayCastOutput output;
    preCast();
    worldRayCastImpl(&output, layer_type);
    return postCast(output);
}

void RayCast::worldRayCastImpl(hkpWorldRayCastOutput* output, ContactLayerType layer_type) {
    hkpWorldRayCastInput input;
    fillCastInput(input, layer_type);

    ScopedWorldLock lock{layer_type, "raycast", 0, OnlyLockIfNeeded::Yes};

    if (mNormalCheckingMode == NormalCheckingMode::DoNotCheck) {
        if (mIgnoredGroups.size() > 0 || int(mIgnoredGroundHit) != GroundHit::Ignore) {
            RayHitCollector collector{output, layer_type,
                                      mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr,
                                      mIgnoredGroundHit};
            System::instance()->getHavokWorld(layer_type)->castRay(input, collector);
        } else {
            System::instance()->getHavokWorld(layer_type)->castRay(input, *output);
        }

    } else {
        sead::Vector3f ray_line = mTo - mFrom;
        ray_line.normalize();

        auto* groups = mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr;
        NormalCheckingRayHitCollector collector(output, ray_line, mNormalCheckingMode, layer_type,
                                                groups, mIgnoredGroundHit);
        System::instance()->getHavokWorld(layer_type)->castRay(input, collector);
    }
}

bool RayCast::shapeRayCast(RigidBody* rigid_body) {
    hkpWorldRayCastOutput output;
    preCast();
    shapeRayCastImpl(&output, rigid_body);
    return postCast(output);
}

void RayCast::shapeRayCastImpl(hkpWorldRayCastOutput* output, RigidBody* body) {
    hkpShapeRayCastInput input;
    auto layer_type = body->getLayerType();
    fillCastInput(input, layer_type);

    sead::Matrix34f transform;
    body->getTransform(&transform);
    transform.invert();
    const auto from = transform * mFrom;
    const auto to = transform * mTo;
    input.m_from = toHkVec4(from);
    input.m_to = toHkVec4(to);

    System::instance()->incrementWorldUnkCounter(ContactLayerType::Entity);
    auto world_guard = sead::makeScopeGuard(
        [&] { System::instance()->decrementWorldUnkCounter(ContactLayerType::Entity); });

    auto* collidable = body->getHkBody()->getCollidable();

    if (mNormalCheckingMode == NormalCheckingMode::DoNotCheck) {
        if (mIgnoredGroups.size() > 0 || int(mIgnoredGroundHit) != GroundHit::Ignore) {
            RayHitCollector collector{output, layer_type,
                                      mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr,
                                      mIgnoredGroundHit};
            collidable->getShape()->castRayWithCollector(input, *collidable, collector);
        } else {
            collidable->getShape()->castRay(input, *output);
        }

    } else {
        sead::Vector3f ray_line = mTo - mFrom;
        ray_line.normalize();

        auto* groups = mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr;
        NormalCheckingRayHitCollector collector(output, ray_line, mNormalCheckingMode, layer_type,
                                                groups, mIgnoredGroundHit);
        collidable->getShape()->castRayWithCollector(input, *collidable, collector);
    }
}

bool RayCast::phantomRayCast(Phantom* phantom) {
    hkpWorldRayCastOutput output;
    preCast();
    phantomRayCastImpl(&output, phantom);
    return postCast(output);
}

void RayCast::phantomRayCastImpl(hkpWorldRayCastOutput* output, Phantom* phantom) {
    hkpWorldRayCastInput input;
    auto layer_type = phantom->getLayerType();
    fillCastInput(input, layer_type);

    ScopedWorldLock lock{layer_type, "raycast", 0, OnlyLockIfNeeded::Yes};

    if (mNormalCheckingMode == NormalCheckingMode::DoNotCheck) {
        if (mIgnoredGroups.size() > 0 || int(mIgnoredGroundHit) != GroundHit::Ignore) {
            RayHitCollector collector{output, layer_type,
                                      mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr,
                                      mIgnoredGroundHit};
            phantom->getHavokPhantom()->castRay(input, collector);
        } else {
            phantom->getHavokPhantom()->castRay(input, *output);
        }

    } else {
        sead::Vector3f ray_line = mTo - mFrom;
        ray_line.normalize();

        auto* groups = mIgnoredGroups.size() > 0 ? &mIgnoredGroups : nullptr;
        NormalCheckingRayHitCollector collector(output, ray_line, mNormalCheckingMode, layer_type,
                                                groups, mIgnoredGroundHit);
        phantom->getHavokPhantom()->castRay(input, collector);
    }
}

void RayCast::updateStaticCompoundObjectInfo(const hkpWorldRayCastOutput& output) {
    hkpShapeKeyPath path{output};
    auto iterator = path.getIterator();

    sead::Vector3f hit_position;
    getHitPosition(&hit_position);

    if (iterator.isValid()) {
        const auto& shape = *iterator.getShape();
        const u32 raw_material = getMaterialMaskFromShape(shape, output.m_shapeKeys, hit_position);

        mMaterialMask.set(raw_material);
        if (raw_material == u32(-1))
            mMaterialMask.reset();

        if (_99) {
            getBodyGroupAndObjectFromSCShape(&mHitBodyGroup, &mHitMapObject, shape,
                                             output.m_shapeKeys);
        }
    } else {
        mMaterialMask.reset();
    }
}

void RayCast::getHitPosition(sead::Vector3f* position) const {
    *position = ((1 - mHitFraction) * mFrom) + (mHitFraction * mTo);
}

static void calculateTriangleNormal(sead::Vector3f* normal, const hkpTriangleShape* triangle) {
    const auto va = toVec3(triangle->getVertex<0>());
    const auto vb = toVec3(triangle->getVertex<1>());
    const auto vc = toVec3(triangle->getVertex<2>());
    normal->setCross(vb - va, vc - va);
}

bool RayCast::getHitTriangleNormal(sead::Vector3f* normal, const hkpShape* hit_shape,
                                   u32 shape_key) const {
    if (hit_shape->getType() != hkcdShapeType::STATIC_COMPOUND) {
        if (hit_shape->getType() != hkcdShapeType::BV_COMPRESSED_MESH)
            return false;

        auto* bv_mesh = static_cast<const hkpBvCompressedMeshShape*>(hit_shape);

        hkpShapeBuffer buffer;
        hit_shape = bv_mesh->getChildShape(shape_key, buffer);
        if (hit_shape->getType() != hkcdShapeType::TRIANGLE)
            return false;

        calculateTriangleNormal(normal, static_cast<const hkpTriangleShape*>(hit_shape));
        return true;
    }

    auto* sc = static_cast<const hkpStaticCompoundShape*>(hit_shape);
    int instance_id;
    sc->decomposeShapeKey(shape_key, instance_id, shape_key);
    return instance_id >= 0 &&
           getHitTriangleNormal(normal, sc->getInstances()[instance_id].getShape(), shape_key);
}

void RayCast::getHitNormal(sead::Vector3f* normal) const {
    *normal = mHitNormal;
}

bool RayCast::getHitTriangleNormal(sead::Vector3f* normal) const {
    if (!mHasHit)
        return false;

    const u32 shape_key = mHitShapeKey;
    const hkpShape* shape = mHitCollidable->getShape();
    return getHitTriangleNormal(normal, shape, shape_key);
}

RayHitCollector::~RayHitCollector() = default;

bool RayHitCollector::isIgnoredGroup(const hkpCdBody& cdBody,
                                     const hkpShapeRayCastCollectorOutput& hitInfo) const {
    if (mIgnoredGroups == nullptr ||
        cdBody.getRootCollidable()->getShape()->getType() == hkcdShapeType::STATIC_COMPOUND) {
        return false;
    }

    auto filter_info = cdBody.getRootCollidable()->getCollisionFilterInfo();
    auto* group_filter = System::instance()->getGroupFilter(mLayerType);
    auto group_idx = int(group_filter->getCollisionFilterInfoGroupHandlerIdx(filter_info));

    if (group_idx != 0) {
        for (int i = 0; i < mIgnoredGroups->size(); ++i) {
            if ((*mIgnoredGroups)[i]->getIndex() == group_idx)
                return true;
        }
    }

    return false;
}

bool RayHitCollector::isIgnoredGroundHit(const hkpCdBody& cdBody,
                                         const hkpShapeRayCastCollectorOutput& hitInfo) const {
    if (mIgnoredGroundHit == GroundHit::Ignore ||
        cdBody.getRootCollidable()->getShape()->getType() == hkcdShapeType::STATIC_COMPOUND ||
        mLayerType != ContactLayerType::Entity) {
        return false;
    }

    auto filter_info = cdBody.getRootCollidable()->getCollisionFilterInfo();
    auto body_ground_hit = EntityCollisionMask(filter_info).getGroundHit();
    if (int(mIgnoredGroundHit) == body_ground_hit)
        return true;

    return false;
}

// NON_MATCHING: group_idx check should be a ccmp
void RayHitCollector::addRayHit(const hkpCdBody& cdBody,
                                const hkpShapeRayCastCollectorOutput& hitInfo) {
    bool closer = hitInfo.m_hitFraction < mOutput->m_hitFraction;
    if (!closer)
        return;

    if (isIgnoredGroup(cdBody, hitInfo))
        return;

    if (isIgnoredGroundHit(cdBody, hitInfo))
        return;

    if (System::instance()->getEntityContactListenerField91() &&
        mLayerType == ContactLayerType::Entity &&
        EntityContactListener::isObjectOrGroundOrNPCOrTree(cdBody)) {
        // XXX: Similar checks show up in various other collectors. Can this be refactored?
        return;
    }

    *static_cast<hkpShapeRayCastCollectorOutput*>(mOutput) = hitInfo;
    mOutput->m_rootCollidable = cdBody.getRootCollidable();
    shapeKeysFromCdBody(mOutput->m_shapeKeys, hkpShapeRayCastOutput::MAX_HIERARCHY_DEPTH, cdBody);
    m_earlyOutHitFraction = hitInfo.m_hitFraction;
}

NormalCheckingRayHitCollector::~NormalCheckingRayHitCollector() = default;

void NormalCheckingRayHitCollector::addRayHit(const hkpCdBody& cdBody,
                                              const hkpShapeRayCastCollectorOutput& hitInfo) {
    bool closer = hitInfo.m_hitFraction < mOutput->m_hitFraction;
    if (!closer)
        return;

    if (isIgnoredGroup(cdBody, hitInfo))
        return;

    if (isIgnoredGroundHit(cdBody, hitInfo))
        return;

    if (!checkNormal(cdBody, hitInfo))
        return;

    if (System::instance()->getEntityContactListenerField91() &&
        mLayerType == ContactLayerType::Entity &&
        EntityContactListener::isObjectOrGroundOrNPCOrTree(cdBody)) {
        return;
    }

    *static_cast<hkpShapeRayCastCollectorOutput*>(mOutput) = hitInfo;
    mOutput->m_rootCollidable = cdBody.getRootCollidable();
    shapeKeysFromCdBody(mOutput->m_shapeKeys, hkpShapeRayCastOutput::MAX_HIERARCHY_DEPTH, cdBody);
    m_earlyOutHitFraction = hitInfo.m_hitFraction;
}

template <bool Invert>
static bool checkDot(RayCast::NormalCheckingMode mode, float dot) {
    if (mode == RayCast::NormalCheckingMode::_0) {
        if constexpr (Invert)
            return !(dot < 0);
        else
            return (dot < 0);
    } else {
        if constexpr (Invert)
            return !(dot > 0);
        else
            return (dot > 0);
    }
}

bool NormalCheckingRayHitCollector::checkNormal(
    const hkpCdBody& cdBody, const hkpShapeRayCastCollectorOutput& hitInfo) const {
    if (cdBody.getShape()->getType() != hkcdShapeType::TRIANGLE)
        return checkDot<false>(mMode, mRayLine->dot(toVec3(hitInfo.m_normal)));

    auto* triangle = static_cast<const hkpTriangleShape*>(cdBody.getShape());

    auto vertexA = triangle->getVertex<0>();
    auto vertexB = triangle->getVertex<1>();
    auto vertexC = triangle->getVertex<2>();

    hkVector4f BminusA;
    BminusA.setSub(vertexB, vertexA);

    hkVector4f CminusA;
    CminusA.setSub(vertexC, vertexA);

    hkVector4f triangle_normal;
    triangle_normal.setCross(BminusA, CminusA);
    triangle_normal.normalize<3>();

    const auto body_rotation = cdBody.getRootCollidable()->getTransform().getRotation();

    hkRotationf rotation = body_rotation;

    if (cdBody.getRootCollidable()->getShape()->getType() == hkcdShapeType::STATIC_COMPOUND) {
        auto* sc =
            static_cast<const hkpStaticCompoundShape*>(cdBody.getRootCollidable()->getShape());

        int instance_id;
        hkpShapeKey child_key;
        sc->decomposeShapeKey(cdBody.getShapeKey(), instance_id, child_key);

        hkRotationf shape_rotation;
        shape_rotation.set(sc->getInstances()[instance_id].getTransform().getRotation());
        rotation.mul(shape_rotation);
    }

    hkVector4f rotated_normal;
    rotated_normal.setRotatedDir(rotation, hitInfo.m_normal);

    return checkDot<true>(mMode, triangle_normal.dot<3>(rotated_normal));
}

}  // namespace ksys::phys
