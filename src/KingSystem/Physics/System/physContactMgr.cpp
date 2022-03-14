#include "KingSystem/Physics/System/physContactMgr.h"
#include <memory>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyRequestMgr.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfoGroup.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::phys {

struct ContactMgr::ImpulseEntry {
    static constexpr size_t getListNodeOffset() { return offsetof(ImpulseEntry, list_node); }

    RigidBody* bodies[2];
    sead::Vector3f linear_vels[2];
    bool is_dynamic_motion[2];
    float magnitude;
    float impulses[2];
    sead::Vector3f contact_point_pos;
    bool is_entity_motion_flag_20_off;
    bool valid;
    sead::ListNode list_node;
};

ContactMgr::ContactMgr() {
    mContactPointInfoInstances.initOffset(ContactPointInfo::getListNodeOffset());
    mCollisionInfoInstances.initOffset(CollisionInfo::getListNodeOffset());
    mLayerColInfoGroups.initOffset(ContactLayerCollisionInfoGroup::getListNodeOffset());
    mCollidingBodiesFreeList.initOffset(CollidingBodies::getListNodeOffset());
    mImpulseEntriesFreeList.initOffset(ImpulseEntry::getListNodeOffset());
    mImpulseEntries.initOffset(ImpulseEntry::getListNodeOffset());
}

ContactMgr::~ContactMgr() {
    for (int i = 0; i < mCollidingBodiesCapacity; ++i)
        delete mCollidingBodiesFreeList.popFront();
}

void ContactMgr::init(sead::Heap* heap) {
    mCollidingBodiesCapacity = 0x2000;
    for (int i = 0; i < mCollidingBodiesCapacity; ++i) {
        mCollidingBodiesFreeList.pushBack(new (heap) CollidingBodies());
    }

    for (int i = 0; i < 0x100; ++i) {
        mImpulseEntriesFreeList.pushBack(new (heap) ImpulseEntry());
    }
}

void ContactMgr::initContactPointPool(sead::Heap* heap, IsIndoorStage indoor) {
    int count = 0x1000;
    if (indoor == IsIndoorStage::Yes)
        count = 0x2000;
    mContactPointPool.allocBufferAssert(count, heap);
}

void ContactMgr::freeContactPointPool() {
    mContactPointPool.freeBuffer();
}

void ContactMgr::loadContactInfoTable(sead::Heap* heap, agl::utl::ResParameterArchive archive,
                                      ContactLayerType type) {
    auto& table = mContactInfoTables[int(type)];

    table.param_io.addList(&table.contact_info_table_plist, "ContactInfoTable");

    const auto root = archive.getRootList();
    const auto num_receivers = root.getResParameterObj(0).getNum();

    if (num_receivers != 0)
        table.receivers.allocBufferAssert(num_receivers, heap);

    doLoadContactInfoTable(archive, type, false);
}

void ContactMgr::doLoadContactInfoTable(agl::utl::ResParameterArchive archive,
                                        ContactLayerType type, bool skip_params) {
    auto& table = mContactInfoTables[int(type)];

    table.contact_info_table_plist.clearObj();

    const auto root = archive.getRootList();
    const auto names = root.getResParameterObj(0);

    const auto* filter = System::instance()->getGroupFilter(type);
    const auto layer_base = static_cast<int>(getContactLayerBase(type));

    for (int i = 0; i < table.receivers.size(); ++i) {
        auto& receiver = table.receivers[i];

        auto* receiver_name = names.getParameterData<const char>(i);
        receiver.name = receiver_name;

        table.contact_info_table_plist.addObj(&receiver, receiver_name);
        receiver.num_layers = filter->getNumLayers();

        if (!skip_params) {
            for (int idx = 0; idx < filter->getNumLayers(); ++idx) {
                const char* layer_name = contactLayerToText(layer_base + idx);
                receiver.layer_values[idx].init(0, layer_name, layer_name, &receiver);
            }
        }
    }

    table.param_io.applyResParameterArchive(archive);
}

ContactPointInfo* ContactMgr::makeContactPointInfo(sead::Heap* heap, int num,
                                                   const sead::SafeString& name, int a, int b,
                                                   int c) {
    auto* info = new (heap) ContactPointInfo(name, a, b, c);
    info->allocPoints(heap, num);
    return info;
}

LayerContactPointInfo* ContactMgr::makeLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                             const sead::SafeString& name, int a,
                                                             int b, int c) {
    auto* info = new (heap) LayerContactPointInfo(name, a, b, c);
    info->allocPoints(heap, num, num2);
    registerContactPointInfo(info);
    return info;
}

CollisionInfo* ContactMgr::makeCollisionInfo(sead::Heap* heap, const sead::SafeString& name) {
    return new (heap) CollisionInfo(name);
}

ContactLayerCollisionInfoGroup*
ContactMgr::makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                               const sead::SafeString& name) {
    auto* group = new (heap) ContactLayerCollisionInfoGroup(layer, name);
    group->init(heap, capacity);
    registerContactLayerCollisionInfoGroup(group);
    return group;
}

void ContactMgr::registerContactPointInfo(ContactPointInfoBase* info) {
    auto lock = sead::makeScopedLock(mContactPointInfoMutex);
    if (!info->isLinked())
        mContactPointInfoInstances.pushBack(info);
}

void ContactMgr::unregisterContactPointInfo(ContactPointInfoBase* info) {
    auto lock = sead::makeScopedLock(mContactPointInfoMutex);
    if (info->isLinked())
        mContactPointInfoInstances.erase(info);
}

void ContactMgr::freeContactPointInfo(ContactPointInfoBase* info) {
    if (!info)
        return;

    unregisterContactPointInfo(info);
    info->freePoints();
    delete info;
}

void ContactMgr::registerCollisionInfo(CollisionInfo* info) {
    auto lock = sead::makeScopedLock(mCollisionInfoMutex);
    if (!info->isLinked())
        mCollisionInfoInstances.pushBack(info);
}

void ContactMgr::unregisterCollisionInfo(CollisionInfo* info) {
    auto lock = sead::makeScopedLock(mCollisionInfoMutex);
    if (info->isLinked())
        mCollisionInfoInstances.erase(info);
}

void ContactMgr::freeCollisionInfo(CollisionInfo* info) {
    if (!info)
        return;

    clearCollisionEntries(info);
    unregisterCollisionInfo(info);
    delete info;
}

void ContactMgr::registerContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group) {
    auto lock = sead::makeScopedLock(mLayerColInfoGroupMutex);
    mLayerColInfoGroups.pushBack(group);
}

void ContactMgr::unregisterContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group) {
    auto lock = sead::makeScopedLock(mLayerColInfoGroupMutex);
    mLayerColInfoGroups.erase(group);
}

void ContactMgr::freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group) {
    if (!group)
        return;

    clearCollisionEntries(group);
    unregisterContactLayerCollisionInfoGroup(group);
    group->finalize();

    delete group;
}

// NON_MATCHING: two sub instructions reordered
void ContactMgr::clearContactPoints() {
    auto lock = sead::makeScopedLock(mContactPointInfoMutex);

    if (mNumContactPoints != 0)
        mNumContactPoints = 0;

    for (auto& info : mContactPointInfoInstances) {
        if (info.mNumContactPoints != 0)
            info.mNumContactPoints = 0;
    }
}

void ContactMgr::removeContactPointsWithBody(RigidBody* body) {
    auto lock = sead::makeScopedLock(mContactPointInfoMutex);
    for (int i = 0; i < mNumContactPoints; ++i) {
        ContactPoint& point = mContactPointPool[i];
        if (point.body_a == body || point.body_b == body)
            point.flags.set(ContactPoint::Flag::Invalid);
    }
}

void ContactMgr::removeCollisionEntriesWithBody(RigidBody* body) {
    auto lock_all_ci = sead::makeScopedLock(mCollisionInfoMutex);
    auto lock_all_cb = sead::makeScopedLock(mCollidingBodiesMutex);

    const auto body_layer = body->getContactLayer();

    for (auto& collision_info : mCollisionInfoInstances) {
        auto lock_ci = sead::makeScopedLock(collision_info);

        // Small optimisation: there's no need to check all colliding bodies in this CI
        // if we know we will never be able to find the body in this CI because the layers mismatch.
        if (!collision_info.isLayerEnabled(body_layer))
            continue;

        for (auto& colliding_pair : collision_info.getCollidingBodies().robustRange()) {
            if (colliding_pair.bodies[1] != body)
                continue;

            collision_info.getCollidingBodies().erase(&colliding_pair);
            mCollidingBodiesFreeList.pushBack(&colliding_pair);
        }
    }
}

void ContactMgr::removeImpulseEntriesWithBody(RigidBody* body) {
    auto lock = sead::makeScopedLock(mImpulseEntriesMutex);

    for (auto& entry : mImpulseEntries.robustRange()) {
        if (entry.bodies[0] == body || entry.bodies[1] == body) {
            mImpulseEntries.erase(&entry);
            mImpulseEntriesFreeList.pushBack(&entry);
        }
    }
}

int ContactMgr::allocateContactPoint() {
    if (mNumContactPoints >= mContactPointPool.size() - 1) {
        util::PrintDebugFmt("contact point pool exhausted (current number of points: %d)",
                            mNumContactPoints.load());
        return -1;
    }
    return mNumContactPoints.increment();
}

bool ContactMgr::registerContactPoint(ContactPointInfo* info, const ContactPoint& point,
                                      const RigidBodyCollisionMasks& colliding_body_masks,
                                      bool penetrating) {
    if (!info->isLinked())
        return false;

    auto disable_contact = ContactPointInfo::ShouldDisableContact::No;

    if (auto* callback = info->getContactCallback()) {
        ContactPointInfo::Event event;
        event.body = point.body_b;
        event.position = &point.position;
        event.separating_normal = &point.separating_normal;
        event.collision_masks = &colliding_body_masks;
        if (!callback->invoke(&disable_contact, event))
            return disable_contact == ContactPointInfo::ShouldDisableContact::Yes;
    }

    int pool_index = allocateContactPoint();
    if (pool_index != -1) {
        auto& point_in_pool = mContactPointPool[pool_index];
        point_in_pool = point;

        if (info->mNumContactPoints < info->mPoints.size() || info->_2c >= 2) {
            int index = info->mNumContactPoints.increment();
            info->mPoints[index] = &point_in_pool;
            info->mPoints[index]->flags.makeAllZero();
            info->mPoints[index]->flags.change(ContactPoint::Flag::Penetrating, penetrating);
        }
    }

    return disable_contact == ContactPointInfo::ShouldDisableContact::Yes;
}

bool ContactMgr::registerContactPoint(QueryContactPointInfo* info, const ContactPoint& point,
                                      bool penetrating) {
    int pool_index = allocateContactPoint();
    if (pool_index == -1)
        return false;

    auto& point_in_pool = mContactPointPool[pool_index];
    point_in_pool = point;

    if (info->mNumContactPoints >= info->mPoints.size() && info->_2c < 2)
        return false;

    int index = info->mNumContactPoints.increment();
    info->mPoints[index] = &point_in_pool;
    info->mPoints[index]->flags.makeAllZero();
    info->mPoints[index]->flags.change(ContactPoint::Flag::Penetrating, penetrating);
    return true;
}

void ContactMgr::registerContactPoint(LayerContactPointInfo* info, const ContactPoint& point,
                                      bool penetrating) {
    int pool_index = allocateContactPoint();
    if (pool_index == -1)
        return;

    auto& point_in_pool = mContactPointPool[pool_index];
    point_in_pool = point;

    if (info->mNumContactPoints < info->mPoints.size()) {
        int index = info->mNumContactPoints.increment();
        info->mPoints[index] = &point_in_pool;
        info->mPoints[index]->flags.makeAllZero();
        info->mPoints[index]->flags.change(ContactPoint::Flag::Penetrating, penetrating);
    }
}

bool ContactMgr::initLayerMasks(ContactPointInfo* info,
                                const sead::SafeString& receiver_name) const {
    for (int type = 0; type < mContactInfoTables.size(); ++type) {
        const auto& receivers = mContactInfoTables[type].receivers;
        for (int i = 0; i < receivers.size(); ++i) {
            const auto& receiver = receivers[i];
            if (receiver_name == receiver.name) {
                info->mSubscribedLayers[type] = receiver.layer_mask;
                info->mLayerMask2[type] = receiver.layer_mask2;
                return true;
            }
        }
    }
    return false;
}

bool ContactMgr::initLayerMasks(CollisionInfo* info, const sead::SafeString& receiver_name) const {
    for (int type = 0; type < mContactInfoTables.size(); ++type) {
        const auto& receivers = mContactInfoTables[type].receivers;
        for (int i = 0; i < receivers.size(); ++i) {
            const auto& receiver = receivers[i];
            if (receiver_name == receiver.name) {
                info->getLayerMask(ContactLayerType(type)) = receiver.layer_mask;
                return true;
            }
        }
    }
    return false;
}

bool ContactMgr::getSensorLayerMask(SensorCollisionMask* mask,
                                    const sead::SafeString& receiver_name) const {
    const auto& receivers = mContactInfoTables[int(ContactLayerType::Sensor)].receivers;
    for (int i = 0; i < receivers.size(); ++i) {
        const auto& receiver = receivers[i];
        if (receiver_name == receiver.name) {
            receiverMaskSetSensorLayerMask(mask, receiver.layer_mask);
            return true;
        }
    }
    return false;
}

void ContactMgr::registerCollision(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    if (!info->isLinked())
        return;

    auto* entry = mCollidingBodiesFreeList.popFront();
    if (entry) {
        entry->bodies[0] = body_a;
        entry->bodies[1] = body_b;
        info->getCollidingBodies().pushBack(entry);
    }
}

void ContactMgr::registerCollision(ContactLayerCollisionInfo* info, RigidBody* body_a,
                                   RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);

    auto* entry = mCollidingBodiesFreeList.popFront();
    if (entry) {
        entry->bodies[0] = body_a;
        entry->bodies[1] = body_b;
        info->getCollidingBodies().pushBack(entry);
    }
}

void ContactMgr::unregisterCollision(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    auto info_lock = sead::makeScopedLock(*info);

    for (auto& entry : info->getCollidingBodies()) {
        if (entry.bodies[0] == body_a && entry.bodies[1] == body_b) {
            info->getCollidingBodies().erase(&entry);
            mCollidingBodiesFreeList.pushBack(&entry);
            break;
        }
    }
}

void ContactMgr::unregisterCollision(ContactLayerCollisionInfo* info, RigidBody* body_a,
                                     RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    auto info_lock = sead::makeScopedLock(*info);

    for (auto& entry : info->getCollidingBodies()) {
        if (entry.bodies[0] == body_a && entry.bodies[1] == body_b) {
            info->getCollidingBodies().erase(&entry);
            freeCollidingBodiesEntry(&entry);
            break;
        }
    }
}

void ContactMgr::unregisterCollisionWithBody(ContactLayerCollisionInfo* info, RigidBody* body) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    auto info_lock = sead::makeScopedLock(*info);

    auto body_layer = body->getContactLayer();

    for (auto& entry : info->getCollidingBodies().robustRange()) {
        auto* body_a = entry.bodies[0];
        auto* body_b = int(body_a->getContactLayer()) == body_layer ? body_a : entry.bodies[1];
        if (body_b == body) {
            info->getCollidingBodies().erase(&entry);
            freeCollidingBodiesEntry(&entry);
        }
    }
}

void ContactMgr::clearCollisionEntries(CollisionInfo* info) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    auto info_lock = sead::makeScopedLock(*info);

    for (auto& entry : info->getCollidingBodies().robustRange()) {
        info->getCollidingBodies().erase(&entry);
        mCollidingBodiesFreeList.pushBack(&entry);
    }
}

void ContactMgr::clearCollisionEntries(ContactLayerCollisionInfoGroup* group) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);

    for (int i = 0; i < group->getCollisionInfo().size(); ++i) {
        ContactLayerCollisionInfo* info = group->getCollisionInfo()[i];
        auto info_lock = sead::makeScopedLock(*info);

        for (auto& entry : info->getCollidingBodies().robustRange()) {
            info->getCollidingBodies().erase(&entry);
            freeCollidingBodiesEntry(&entry);
        }
    }
}

void ContactMgr::addImpulseEntry(RigidBody* body_a, RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mImpulseEntriesMutex);

    auto* entry = mImpulseEntriesFreeList.popFront();
    if (!entry)
        return;

    entry->bodies[0] = body_a;
    entry->bodies[1] = body_b;
    body_a->getLinearVelocity(&entry->linear_vels[0]);
    body_b->getLinearVelocity(&entry->linear_vels[1]);
    entry->is_dynamic_motion[0] = body_a->getMotionType() == MotionType::Dynamic;
    entry->is_dynamic_motion[1] = body_b->getMotionType() == MotionType::Dynamic;
    entry->magnitude = 0;
    entry->impulses[0] = 0;
    entry->impulses[1] = 0;
    entry->is_entity_motion_flag_20_off = true;
    entry->valid = false;
    mImpulseEntries.pushBack(entry);
}

static sead::Vector3f computeLinearVelocity(const RigidBody& body, const sead::Vector3f& linear_vel,
                                            const sead::Vector3f& pos) {
    const auto center = body.getCenterOfMassInWorld();
    const auto rel_pos = pos - center;
    sead::Vector3f correction;
    correction.setCross(body.getAngularVelocity(), rel_pos);
    return linear_vel + correction;
}

void ContactMgr::setImpulseEntryContactInfo(RigidBody* body_a, RigidBody* body_b,
                                            const sead::Vector3f& contact_point_pos,
                                            const sead::Vector3f& contact_point_normal,
                                            u32 material_a, u32 material_b) {
    auto lock = sead::makeScopedLock(mImpulseEntriesMutex);

    ImpulseEntry* entry = nullptr;
    for (auto& impulse_entry : mImpulseEntries) {
        if ((impulse_entry.bodies[0] == body_a && impulse_entry.bodies[1] == body_b) ||
            (impulse_entry.bodies[1] == body_a && impulse_entry.bodies[0] == body_b)) {
            entry = std::addressof(impulse_entry);
            break;
        }
    }

    if (!entry)
        return;

    const MaterialMask mat_mask_a{material_a};
    const MaterialMask mat_mask_b{material_b};

    if (mat_mask_a.getData().flag30 || mat_mask_b.getData().flag30)
        return;

    if (mat_mask_a.getFloorCode() == FloorCode::NoImpulseUpperMove && entry->linear_vels[0].y > 0)
        return;

    if (mat_mask_b.getFloorCode() == FloorCode::NoImpulseUpperMove && entry->linear_vels[1].y > 0)
        return;

    /// The velocities of the rigid bodies at the contact point.
    const auto linvel_a =
        computeLinearVelocity(*entry->bodies[0], entry->linear_vels[0], contact_point_pos);
    const auto linvel_b =
        computeLinearVelocity(*entry->bodies[1], entry->linear_vels[1], contact_point_pos);

    const bool is_flag_off =
        entry->bodies[0]->isEntityMotionFlag20Off() && entry->bodies[1]->isEntityMotionFlag20Off();

    /// The pre-collision relative velocity.
    const auto relative_vel = linvel_a - linvel_b;
    const auto dot_neg = [&](const auto& vec) { return vec.dot(-contact_point_normal); };

    float magnitude = is_flag_off ? sead::Mathf::max(0.0, relative_vel.dot(-contact_point_normal)) :
                                    sead::Mathf::max(0.0, relative_vel.length());

    if (magnitude >= entry->magnitude) {
        float i1, i2;
        if (is_flag_off) {
            i1 = sead::Mathf::min(sead::Mathf::max(0.0, dot_neg(linvel_a)), magnitude);
            i2 = sead::Mathf::min(sead::Mathf::max(0.0, linvel_b.dot(contact_point_normal)),
                                  sead::Mathf::max(0.0, dot_neg(relative_vel)));
        } else {
            i1 = sead::Mathf::min(sead::Mathf::max(0.0, linvel_a.length()), magnitude);
            i2 = sead::Mathf::min(sead::Mathf::max(0.0, linvel_b.length()),
                                  sead::Mathf::max(0.0, relative_vel.length()));
        }

        entry->magnitude = magnitude;
        entry->impulses[0] = i1;
        entry->impulses[1] = i2;
        entry->contact_point_pos = contact_point_pos;
        entry->is_entity_motion_flag_20_off = is_flag_off;
        entry->valid = true;
    }
}

inline void ContactMgr::processImpulseEntry(const ImpulseEntry& entry) {
    if (!entry.valid)
        return;

    RigidBody* body_a = entry.bodies[0];
    RigidBody* body_b = entry.bodies[1];

    if (body_a->isEntityMotionFlag40On())
        body_a->setEntityMotionFlag40(false);

    if (body_b->isEntityMotionFlag40On())
        body_b->setEntityMotionFlag40(false);

    float impulse_a = 0.0f;
    float impulse_b = 0.0f;

    const auto compute_impulse = [&entry](int index, RigidBody* body) {
        if (!entry.is_dynamic_motion[index])
            return 0.0f;

        const auto impulse = entry.impulses[index];
        if (!(impulse > 5.0f || !entry.is_entity_motion_flag_20_off))
            return 0.0f;

        const float scaled_impulse = impulse * body->getMass() * body->getColImpulseScale();

        float volume_factor = 1.0f;
        if (body->getMotionType() == MotionType::Dynamic)
            volume_factor += util::clampAndRemapRange(body->getVolume(), 0.2, 1.0, 1.0, 0.0);
        return scaled_impulse * volume_factor;
    };

    impulse_b = compute_impulse(0, body_a);
    impulse_a = compute_impulse(1, body_b);

    const auto add_impulse = [impulse_a, impulse_b](RigidBody* body1, RigidBody* body2,
                                                    float impulse) {
        if (body1->isEntityMotionFlag10Off())
            impulse = impulse_a + impulse_b;

        if (body2->isEntityMotionFlag8On() ||
            (body1->getMaxImpulse() >= 0 && impulse > body1->getMaxImpulse())) {
            System::instance()->getRigidBodyRequestMgr()->addImpulse(body1, body2, impulse);
        }
    };
    add_impulse(body_a, body_b, impulse_a);
    add_impulse(body_b, body_a, impulse_b);
}

void ContactMgr::processImpulseEntries() {
    auto lock = sead::makeScopedLock(mImpulseEntriesMutex);

    for (auto& entry : mImpulseEntries.robustRange()) {
        processImpulseEntry(entry);
        mImpulseEntries.erase(&entry);
        mImpulseEntriesFreeList.pushBack(&entry);
    }
}

void ContactMgr::clearImpulseEntries() {
    auto lock = sead::makeScopedLock(mImpulseEntriesMutex);

    for (auto& entry : mImpulseEntries.robustRange()) {
        mImpulseEntries.erase(&entry);
        mImpulseEntriesFreeList.pushBack(&entry);
    }
}

void ContactInfoTable::Receiver::postRead_() {
    layer_mask = 0;
    layer_mask2 = 0;

    for (int i = 0; i < num_layers; ++i) {
        const auto value = layer_values[i].ref();
        if (value & 1)
            layer_mask |= 1 << i;
        if (value & 2)
            layer_mask2 |= 1 << i;
    }
}

}  // namespace ksys::phys
