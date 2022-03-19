#include "KingSystem/Physics/System/physRayCast.h"
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Havok/Physics2012/Collide/Query/hkpRayHitCollector.h>
#include <Havok/Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorld.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/System/physEntityContactListener.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
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

    NormalCheckingRayHitCollector(hkpWorldRayCastOutput* output, ContactLayerType layer_type,
                                  const sead::PtrArray<SystemGroupHandler>* ignored_groups,
                                  GroundHit ignored_ground_hit, const sead::Vector3f* ray_line,
                                  RayCast::NormalCheckingMode mode)
        : RayHitCollector(output, layer_type, ignored_groups, ignored_ground_hit),
          mRayLine(ray_line), mMode(mode) {}

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
    mExtraGroupHandlers.clear();

    resetCastResult();
}

void RayCast::resetCastResult() {
    static_cast<void>(_98.load());

    _30 = {};
    _34 = sead::Vector3f::zero;
    mHitFraction = -1.0;
    _48 = {};
    _50 = {};
    _54 = {};
    _58 = {};
    _60 = {};
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

void RayCast::setD8(int value) {
    _d8 = value;
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

bool RayCast::addGroupHandler(SystemGroupHandler* group_handler) {
    if (mExtraGroupHandlers.size() == mExtraGroupHandlers.capacity() || group_handler == nullptr)
        return false;

    mExtraGroupHandlers.pushBack(group_handler);
    return true;
}

void RayCast::setRigidBody(RigidBody* body) {
    if (_70 != 1)
        mRigidBody = body;
}

void RayCast::getHitPosition(sead::Vector3f* out) const {
    *out = ((1 - mHitFraction) * mFrom) + (mHitFraction * mTo);
}

void RayCast::get34(sead::Vector3f* out) const {
    *out = _34;
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

    hkVector4f triangle_line;
    triangle_line.setCross(BminusA, CminusA);
    triangle_line.normalize<3>();

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

    return checkDot<true>(mMode, triangle_line.dot<3>(rotated_normal));
}

}  // namespace ksys::phys
