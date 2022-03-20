#include "KingSystem/Physics/System/physShapeCast.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdPoint.h>
#include <Havok/Physics2012/Collide/Agent/hkpProcessCollisionInput.h>
#include <Havok/Physics2012/Collide/Query/CastUtil/hkpLinearCastInput.h>
#include <Havok/Physics2012/Collide/Query/Collector/PointCollector/hkpAllCdPointCollector.h>
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physEntityContactListener.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physLayerMaskBuilder.h"

namespace ksys::phys {

ShapeCast::ShapeCast(RigidBody* body, QueryContactPointInfo* contact_point_info, Mode mode)
    : mContactPointInfo(contact_point_info), mMode(mode) {
    if (body)
        mBody = body;

    mTo = sead::Vector3f::zero;
    mFrom = sead::Vector3f::zero;
    mRotation.set(1, 0, 0, 0);
    reset();
}

ShapeCast::~ShapeCast() = default;

void ShapeCast::reset() {
    _40 = {};
    _41 = {};
    _42 = {};
    _44 = {};

    if (mContactPointInfo)
        mContactPointInfo->getNumContactPoints() = 0;
}

void ShapeCast::setRotation(sead::Quatf rotation) {
    mRotation = rotation;
}

void ShapeCast::setRotation(const sead::Matrix33f& rotation_matrix) {
    auto quat = sead::Quatf::unit;
    rotation_matrix.toQuat(quat);
    setRotation(quat);
}

void ShapeCast::setRotation(const sead::Matrix34f& transform_matrix) {
    auto quat = sead::Quatf::unit;
    transform_matrix.toQuat(quat);
    setRotation(quat);
}

void ShapeCast::setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end) {
    mFrom = start;
    mTo = end;
}

void ShapeCast::setStartAndDisplacement(const sead::Vector3f& start,
                                        const sead::Vector3f& displacement) {
    mFrom = start;
    mTo = start + displacement;
}

void ShapeCast::setStartAndDisplacementScaled(const sead::Vector3f& start,
                                              const sead::Vector3f& displacement,
                                              float displacement_scale) {
    mFrom = start;
    mTo = start + displacement * displacement_scale;
}

void ShapeCast::setLayerMasks(const LayerMaskBuilder& mask_builder) {
    mContactPointInfo->setLayerMasks(mask_builder);
}

void ShapeCast::setColors(const sead::Color4f& color1, const sead::Color4f& color2,
                          const sead::Color4f& color3, bool enabled) {
    // Stubbed in release builds.
}

// NON_MATCHING: the last if block is a complete mess. Should be equivalent, though.
bool ShapeCast::doExecuteQuery(hkpCdPointCollector& cast_collector,
                               hkpAllCdPointCollector* start_collector,
                               ShapeCast::WeldClosestPoints weld_closest_points,
                               OnlyLockIfNeeded only_lock_if_needed) {
    const auto layer_type = mBody->getLayerType();

    {
        ScopedWorldLock lock{layer_type, "shape_cast", 0, only_lock_if_needed};

        hkpLinearCastInput input;
        loadFromVec3(&input.m_to, mTo);

        // Reset internal state.
        cast_collector.reset();
        if (_44 == 1)
            reset();

        System::instance()->getHavokWorld(layer_type)->m_collisionInput->m_weldClosestPoints =
            bool(weld_closest_points);

        doCast(input, cast_collector, start_collector);
    }

    // Register every point that is in start_collector.
    auto* body = mBody;
    for (int i = 0, n = start_collector->getNumHits(); i < n; ++i) {
        if (registerContactPoint(start_collector->getHits()[i], body, ClampDistance::Yes)) {
            _40 = true;
            if (mMode == Mode::_0)
                break;
        }
    }

    _41 = _40;

    if (mMode == Mode::_2 || !_40) {
        int num_hits = 0;
        FilteredClosestCdPointCollector* filtered_collector = nullptr;
        hkpAllCdPointCollector* all_point_collector = nullptr;
        bool ok = false;

        if (mMode == Mode::_1 || mMode == Mode::_0) {
            filtered_collector = static_cast<FilteredClosestCdPointCollector*>(&cast_collector);
            num_hits = 1;
            ok = filtered_collector->hasHit();
        } else {
            all_point_collector = static_cast<hkpAllCdPointCollector*>(&cast_collector);
            num_hits = all_point_collector->getNumHits();
            ok = num_hits >= 0;
        }

        if (ok) {
            for (int i = 0; i < num_hits; ++i) {
                const auto& point = mMode == Mode::_2 ? all_point_collector->getHits()[i] :
                                                        filtered_collector->getHit();
                if (registerContactPoint(point, body, ClampDistance::No))
                    _40 = true;
            }
        }

        _42 = _40;
    }

    _44 = 1;
    return _40;
}

bool ShapeCast::registerContactPoint(const hkpRootCdPoint& point, RigidBody* body,
                                     ClampDistance clamp_distance) {
    auto* hit_entity = getHkpEntity(*point.m_rootCollidableB);
    if (!hit_entity)
        return false;

    if (!mContactPointInfo->testContactPointDistance(point.getContact().getDistance()))
        return false;

    auto* hit_body = getRigidBody(*hit_entity);

    if (System::instance()->getEntityContactListenerField91() && hit_body->isEntity() &&
        EntityContactListener::isObjectOrGroundOrNPCOrTree(*hit_body)) {
        return false;
    }

    RigidBodyCollisionMasks masks_a, masks_b;
    sead::Vector3f contact_position;
    storeToVec3(&contact_position, point.getContact().getPosition());

    body->getCollisionMasks(&masks_a, &point.m_shapeKeyA, contact_position);
    hit_body->getCollisionMasks(&masks_b, &point.m_shapeKeyB, contact_position);

    auto* filter = System::instance()->getGroupFilter(hit_body->getLayerType());
    auto layer_b = filter->getCollisionFilterInfoLayer(masks_b.collision_filter_info);

    if (!mContactPointInfo->isLayerSubscribed(layer_b))
        return false;

    ContactPoint contact_point;
    contact_point.flags.makeAllZero();
    contact_point.body_a = body;
    contact_point.body_b = hit_body;
    contact_point.material_mask_a = MaterialMaskData(masks_a.material_mask);
    contact_point.material_mask_b = MaterialMaskData(masks_b.material_mask);
    storeToVec3(&contact_point.position, point.getContact().getPosition());
    storeToVec3(&contact_point.separating_normal, point.getContact().getSeparatingNormal());

    float distance = point.getContact().getDistance();
    if (distance < 0 && bool(clamp_distance))
        distance = 0;

    contact_point.separating_distance = distance;
    contact_point.shape_key_a = point.m_shapeKeyA;
    contact_point.shape_key_b = point.m_shapeKeyB;
    contact_point.separating_normal *= -1;

    return System::instance()->getContactMgr()->registerContactPoint(mContactPointInfo,
                                                                     contact_point, true);
}

FilteredClosestCdPointCollector::FilteredClosestCdPointCollector(
    RigidBody* body, QueryContactPointInfo* contact_point_info)
    : mBody(body), mContactPointInfo(contact_point_info) {}

// NON_MATCHING: the original code has a useless `if (this == nullptr)` check for some reason
FilteredClosestCdPointCollector::~FilteredClosestCdPointCollector() = default;

void FilteredClosestCdPointCollector::addCdPoint(const hkpCdPoint& point) {
    auto* body = mBody;
    const auto point_distance = point.getContact().getDistanceSimdReal();

    if (hasHit() && !point_distance.isLess(getHitContact().getDistanceSimdReal()))
        return;

    auto* hit_entity = getHkpEntity(*point.m_cdBodyB.getRootCollidable());
    if (!hit_entity)
        return;

    auto* hit_body = getRigidBody(*hit_entity);

    if (System::instance()->getEntityContactListenerField91() && hit_body->isEntity() &&
        EntityContactListener::isObjectOrGroundOrNPCOrTree(*hit_body)) {
        return;
    }

    RigidBodyCollisionMasks masks_a, masks_b;
    sead::Vector3f contact_position;
    storeToVec3(&contact_position, point.getContact().getPosition());
    auto shape_key_a = point.m_cdBodyA.getShapeKey();
    auto shape_key_b = point.m_cdBodyB.getShapeKey();

    body->getCollisionMasks(&masks_a, &shape_key_a, contact_position);
    hit_body->getCollisionMasks(&masks_b, &shape_key_b, contact_position);

    auto* filter = System::instance()->getGroupFilter(hit_body->getLayerType());
    auto layer_b = filter->getCollisionFilterInfoLayer(masks_b.collision_filter_info);

    if (!mContactPointInfo->isLayerSubscribed(layer_b))
        return;

    m_hitPoint.setContact(point.getContact());
    m_hitPoint.m_rootCollidableA = point.m_cdBodyA.getRootCollidable();
    m_hitPoint.m_shapeKeyA = point.m_cdBodyA.getShapeKey();
    m_hitPoint.m_rootCollidableB = point.m_cdBodyB.getRootCollidable();
    m_hitPoint.m_shapeKeyB = point.m_cdBodyB.getShapeKey();
    // Set m_earlyOutDistance to the current distance as an optimisation.
    m_earlyOutDistance = point_distance;
    m_unweldedNormal = point.getUnweldedNormal();
}

void FilteredClosestCdPointCollector::reset() {
    hkpClosestCdPointCollector::reset();
    m_earlyOutDistance = 1.0f;
}

}  // namespace ksys::phys
