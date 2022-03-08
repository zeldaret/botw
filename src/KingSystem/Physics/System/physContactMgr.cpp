#include "KingSystem/Physics/System/physContactMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactLayerCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Utils/Debug.h"

namespace ksys::phys {

ContactMgr::ContactMgr() {
    mContactPointInfoInstances.initOffset(ContactPointInfo::getListNodeOffset());
    // FIXME: figure out what these offsets are
    mCollisionInfoInstances.initOffset(CollisionInfo::getListNodeOffset());
    mList3.initOffset(0x40);
    mCollidingBodiesFreeList.initOffset(CollidingBodies::getListNodeOffset());
    mList4.initOffset(0x48);
    mList5.initOffset(0x48);
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
            if (colliding_pair.body_b != body)
                continue;

            collision_info.getCollidingBodies().erase(&colliding_pair);
            mCollidingBodiesFreeList.pushBack(&colliding_pair);
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
        entry->body_a = body_a;
        entry->body_b = body_b;
        info->getCollidingBodies().pushBack(entry);
    }
}

void ContactMgr::registerCollision(ContactLayerCollisionInfo* info, RigidBody* body_a,
                                   RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);

    auto* entry = mCollidingBodiesFreeList.popFront();
    if (entry) {
        entry->body_a = body_a;
        entry->body_b = body_b;
        info->getCollidingBodies().pushBack(entry);
    }
}

void ContactMgr::unregisterCollision(CollisionInfo* info, RigidBody* body_a, RigidBody* body_b) {
    auto lock = sead::makeScopedLock(mCollidingBodiesMutex);
    auto info_lock = sead::makeScopedLock(*info);

    for (auto& entry : info->getCollidingBodies()) {
        if (entry.body_a == body_a && entry.body_b == body_b) {
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
        if (entry.body_a == body_a && entry.body_b == body_b) {
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
        auto* body_a = entry.body_a;
        auto* body_b = int(body_a->getContactLayer()) == body_layer ? body_a : entry.body_b;
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
