#include "Game/AutoPlacement/AutoPlacementRoadNpc.h"
#include <cmath>
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actRoadNpcRuntimeTypeInfo.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/VFR.h"

namespace uking {

bool RoadNpcPlacementMgr::init(sead::Heap* heap) {
    mInfo.init(heap, true);
    return true;
}

bool RoadNpcPlacementMgr::hasPendingSpawn() const {
    if (mSpawnState.handle.getUnit() != nullptr)
        return true;
    return mSpawnState.handle.hasFailed();
}

void RoadNpcPlacementMgr::finishSpawn() {
    if (!mSpawnState.handle.isProcReady() && !mSpawnState.handle.hasProcCreationFailed())
        return;

    mCreateWait = u32(f32(ksys::VFR::instance()->getFrameRate()) * 0.0f);
    if (mSpawnState.handle.isProcReady()) {
        auto* proc = mSpawnState.handle.getProc();
        const auto* type_info = ksys::act::getRoadNpcRuntimeTypeInfo();
        if (proc != nullptr && proc->checkDerivedRuntimeTypeInfo(type_info)) {
            mSpawnState.handle.releaseAndWakeProc();
            if (mSpawnState.pendingEntry != nullptr)
                mSpawnState.pendingEntry->flags |= 1;
        }
        mSpawnState.handle.deleteProc();
    } else {
        mSpawnState.handle.deleteProcIfFailed();
    }
    if (mSpawnState.pendingEntry != nullptr)
        mSpawnState.pendingEntry->flags &= ~u16(0x10);
    mSpawnState.pendingEntry = nullptr;
}

void RoadNpcPlacementMgr::update() {
    if (ksys::act::BaseProcMgr::instance()->getMode() != ksys::act::BaseProcMgr::Mode::_0 ||
        ksys::evt::Manager::instance()->hasActiveEvent())
        return;

    if (mCreateWait != 0)
        --mCreateWait;
    bool pending = false;
    for (auto& entry : mEntries)
        pending |= entry.update(mUpdatePending);
    mUpdatePending = pending;
}

bool RoadNpcPlacementEntry::update(bool pending) {
    auto* process = proc.getProc(nullptr);
    const auto* type_info = ksys::act::getRoadNpcRuntimeTypeInfo();
    if (process == nullptr || !process->checkDerivedRuntimeTypeInfo(type_info))
        return false;
    auto* actor = static_cast<ksys::act::Actor*>(process);
    if (actor->isSleep()) {
        if (actor->_1a0 != nullptr ||
            (actor->mMapObject != nullptr &&
             (actor->mMapObject->getFlags0().getDirect() & 0x20000) != 0) ||
            (actor->mSchedule != nullptr && actor->mSchedule->_2fc > 0) ||
            actor->mLodState == nullptr || !actor->mLodState->mFlags8.isOnBit(6))
            return true;
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return false;
    }
    if (!actor->isInitialized() || (flags & 8) != 0)
        return false;
    sead::Vector3f direction = navigation.mPreviousPosition - position;
    const f32 distance = direction.normalize();
    position += direction * (pending ? 0.05f : 0.2f);
    if (distance < 0.3f)
        navigation.advance(nullptr, nullptr, 10.0f);
    f32 yaw = 0.0f;
    if (navigation.hasNextRail()) {
        direction.set(navigation.mPreviousPosition.x - navigation.mPosition.x, 0.0f,
                      navigation.mPreviousPosition.z - navigation.mPosition.z);
        if (direction.normalize() != 0.0f)
            yaw = std::atan2(direction.x, direction.z);
    }
    const sead::Vector3f rotation{0.0f, yaw, 0.0f};
    actor->setTransform(&position, &rotation, nullptr);
    return false;
}

bool AutoPlacementInfo::findPoints(const sead::Vector3f& position, bool apply_filter,
                                   s32 filter_mask, AutoPlacementPointResults* results,
                                   f32 scale_multiplier) {
    results->count = 0;
    const s32 x = sead::Mathi::clamp((s32(position.x) + 5000) / 1000, 0, 9);
    const s32 z = sead::Mathi::clamp((s32(position.z) + 4000) / 1000, 0, 7);
    gatherPoints(x, z, position, apply_filter, filter_mask, results, nullptr, scale_multiplier);
    gatherPoints(x - 1, z - 1, position, apply_filter, filter_mask, results, nullptr,
                 scale_multiplier);
    gatherPoints(x, z - 1, position, apply_filter, filter_mask, results, nullptr, scale_multiplier);
    gatherPoints(x + 1, z - 1, position, apply_filter, filter_mask, results, nullptr,
                 scale_multiplier);
    gatherPoints(x - 1, z, position, apply_filter, filter_mask, results, nullptr, scale_multiplier);
    gatherPoints(x + 1, z, position, apply_filter, filter_mask, results, nullptr, scale_multiplier);
    gatherPoints(x - 1, z + 1, position, apply_filter, filter_mask, results, nullptr,
                 scale_multiplier);
    gatherPoints(x, z + 1, position, apply_filter, filter_mask, results, nullptr, scale_multiplier);
    gatherPoints(x + 1, z + 1, position, apply_filter, filter_mask, results, nullptr,
                 scale_multiplier);
    return results->count > 0;
}

bool RoadNpcPlacementMgr::createFromPoint(RoadNpcSpawnState* state, bool rest_station,
                                          const sead::Vector3f* rotation,
                                          bool use_special_create_flag) {
    auto* entry = state->pendingEntry;
    const sead::Vector3f position = entry->position;
    ksys::act::InstParamPack params;
    params->addPosition(position);
    params->addRotation(*rotation);
    params->addDelegate(&entry->createDelegate);
    if (rest_station) {
        params->add(use_special_create_flag ? 9 : 8, "@I");
        entry->flags |= 8;
        const auto& player = AutoPlacementMgr::instance()->mPreviousPlayerPosition;
        const f32 dx = entry->position.x - player.x;
        const f32 dz = entry->position.z - player.z;
        const f32 distance = std::sqrt(dx * dx + dz * dz) + 5.0f;
        params->addDeleteDistanceSq(distance * distance);
    }
    entry->flags |= 0x10;
    return ksys::act::ActorCreator::instance()->requestCreateActor(
        entry->name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &state->handle,
        &params, nullptr, 0);
}

void RoadNpcPlacementMgr::selectSpawn() {
    if (!mEnabled)
        return;
    for (auto& entry : mEntries) {
        if (AutoPlacementMgr::instance()->auto9() ||
            ksys::act::BaseProcMgr::instance()->getMode() != ksys::act::BaseProcMgr::Mode::_0 ||
            ksys::evt::Manager::instance()->hasActiveEvent())
            continue;
        if (!entry.canSpawn(mUpdatePending) || mSpawnState.pendingEntry != nullptr ||
            mCreateWait != 0 || mSpawnState.handle.getUnit() != nullptr ||
            mSpawnState.handle.hasFailed())
            continue;
        mSpawnState.pendingEntry = &entry;
        AutoPlacementPointResults results;
        if ((entry.flags & 0x20) == 0) {
            const s32 mask = (entry.flags & 0x40) != 0 ? 4 : 1;
            if (!entry.info->findPoints(entry.position, true, mask, &results, 50.0f))
                continue;
            s32 point_idx = 0;
            for (; point_idx < results.count; ++point_idx) {
                bool occupied = false;
                for (const auto& other : mEntries) {
                    if ((other.flags & 8) == 0)
                        continue;
                    const f32 dx = other.position.x - results.points[point_idx].position.x;
                    const f32 dz = other.position.z - results.points[point_idx].position.z;
                    if (dx * dx + dz * dz < 0.01f) {
                        occupied = true;
                        break;
                    }
                }
                if (!occupied)
                    break;
            }
            if (point_idx >= results.count || (entry.flags & 0x80) != 0)
                continue;
            const auto& point = results.points[point_idx];
            entry.position = point.position;
            createFromPoint(&mSpawnState, true, &point.rotation, (point.filterMask & 2) != 0);
        } else {
            f32 yaw = 0.0f;
            if (entry.navigation.hasNextRail()) {
                const auto& previous = entry.navigation.mPreviousPosition;
                const auto& target = entry.navigation.mPosition;
                sead::Vector3f direction{previous.x - target.x, 0.0f, previous.z - target.z};
                if (direction.normalize() != 0.0f)
                    yaw = std::atan2(direction.x, direction.z);
            }
            const sead::Vector3f rotation{0.0f, yaw, 0.0f};
            ksys::act::InstParamPack params;
            params->addPosition(mSpawnState.pendingEntry->position);
            params->addRotation(rotation);
            params->addDelegate(&mSpawnState.pendingEntry->createDelegate);
            mSpawnState.pendingEntry->flags |= 0x10;
            ksys::act::ActorCreator::instance()->requestCreateActor(
                mSpawnState.pendingEntry->name.cstr(),
                ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &mSpawnState.handle,
                &params, nullptr, 0);
        }
    }
}

}  // namespace uking
