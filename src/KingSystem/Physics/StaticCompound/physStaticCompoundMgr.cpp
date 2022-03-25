#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundInfo.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundRigidBodyGroup.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

StaticCompoundMgr::StaticCompoundMgr() = default;

StaticCompoundMgr::~StaticCompoundMgr() {
    if (mGroupHandler) {
        System::instance()->removeSystemGroupHandler(mGroupHandler);
        mGroupHandler = nullptr;
    }
}

bool StaticCompoundMgr::init() {
    if (!mGroupHandler)
        mGroupHandler = System::instance()->addSystemGroupHandler(ContactLayerType::Entity);

    return true;
}

void StaticCompoundMgr::addStaticCompound(StaticCompound* sc) {
    auto lock = sead::makeScopedLock(mCS);

    if (mStaticCompounds.indexOf(sc) < 0)
        mStaticCompounds.pushBack(sc);
}

void StaticCompoundMgr::removeStaticCompound(StaticCompound* sc) {
    auto lock = sead::makeScopedLock(mCS);

    int index = mStaticCompounds.indexOf(sc);
    if (index >= 0)
        mStaticCompounds.erase(index);
}

void StaticCompoundMgr::resetExtraTransformsAndApply() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mStaticCompounds.size(); i < n; ++i)
        mStaticCompounds[i]->resetExtraTransformsAndApply();
}

// NON_MATCHING: should be a tail call but somehow isn't
StaticCompoundRigidBodyGroup* StaticCompoundMgr::getBodyGroup(int group_index) const {
    if (mStaticCompounds.size() < 1)
        return nullptr;

    return mStaticCompounds[0]->getFieldBodyGroup(group_index + 1);
}

bool StaticCompoundMgr::hasBodyGroup(const StaticCompoundRigidBodyGroup* group) const {
    if (!group)
        return false;

    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mStaticCompounds.size(); i < n; ++i) {
        if (!mStaticCompounds[i]->isInitialised())
            continue;
        if (!mStaticCompounds[i]->hasFieldBodyGroup(group))
            continue;

        return true;
    }

    return false;
}

void StaticCompoundMgr::processUpdates() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mStaticCompounds.size(); i < n; ++i)
        mStaticCompounds[i]->processUpdates();
}

void StaticCompoundMgr::recomputeTransformMatrix() {
    auto lock = sead::makeScopedLock(mCS);

    for (int i = 0, n = mStaticCompounds.size(); i < n; ++i)
        mStaticCompounds[i]->recomputeTransformMatrix();
}

sead::Matrix34f
StaticCompoundMgr::getTransformedMatrix(StaticCompoundRigidBodyGroup* const& p_group,
                                        const sead::Matrix34f& mtx) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return mtx;
    return group->getTransformedMatrix(mtx);
}

sead::Matrix34f
StaticCompoundMgr::getInvTransformedMatrix(StaticCompoundRigidBodyGroup* const& p_group,
                                           const sead::Matrix34f& mtx) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return mtx;
    return group->getInvTransformedMatrix(mtx);
}

sead::Vector3f StaticCompoundMgr::getTransformedPos(StaticCompoundRigidBodyGroup* const& p_group,
                                                    const sead::Vector3f& pos) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return pos;
    return group->getTransformedPos(pos);
}

sead::Vector3f StaticCompoundMgr::getRotatedDir(StaticCompoundRigidBodyGroup* const& p_group,
                                                const sead::Vector3f& dir) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return dir;
    return group->getRotatedDir(dir);
}

void StaticCompoundMgr::setExtraTransform(StaticCompoundRigidBodyGroup* const& p_group,
                                          const sead::Matrix34f& transform, int index) {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return;
    group->setExtraTransform(transform, index);
}

const sead::Matrix34f&
StaticCompoundMgr::getExtraTransform(StaticCompoundRigidBodyGroup* const& p_group,
                                     int index) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return sead::Matrix34f::ident;
    return group->getExtraTransform(index);
}

RigidBody* StaticCompoundMgr::getRigidBody(StaticCompoundRigidBodyGroup* const& p_group) const {
    auto* group = p_group;
    if (!hasBodyGroup(group))
        return nullptr;

    for (int i = 0; i < NumBodyLayerTypes; ++i) {
        if (auto* body = group->getRigidBody(BodyLayerType(i)))
            return body;
    }

    return nullptr;
}

void StaticCompoundMgr::getBodyGroupAndMapObject(StaticCompoundRigidBodyGroup** p_group,
                                                 map::Object** p_map_object,
                                                 const hkpStaticCompoundShape& shape,
                                                 const u32* shape_key) const {
    auto* group = reinterpret_cast<StaticCompoundRigidBodyGroup*>(shape.getUserData());

    int instance_id;
    hkpShapeKey child_key;
    auto extract_key = [&] {
        shape.decomposeShapeKey(*shape_key, instance_id, child_key);
        return instance_id != -1;
    };

    if (!group || !extract_key()) {
        *p_group = nullptr;
        *p_map_object = nullptr;
    } else {
        auto object_idx = static_cast<int>(shape.getInstanceUserData(instance_id));
        auto* sc = group->getStaticCompound();
        *p_group = group;
        *p_map_object = sc->getMapObject(object_idx);
    }
}

}  // namespace ksys::phys
