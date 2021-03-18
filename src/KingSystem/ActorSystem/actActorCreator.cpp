#include "KingSystem/ActorSystem/actActorCreator.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorTemplate.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcCreateTask.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorCreator)

ActorCreator::ActorCreator() {
    mActorList.initOffset(Actor::getCreatorListNodeOffset());
    mActorFactory = nullptr;
    mEnableDistanceChecks = false;
    mBlockSpawns = false;
    _5a = true;
    mForBaseProcDualHeap = nullptr;
    mPlacementMgrHeap = nullptr;
}

void ActorCreator::onTaskRemoved(const util::TaskRemoveCallbackContext& context) {
    if (!context.mTask)
        return;

    auto* task = sead::DynamicCast<BaseProcCreateTask>(context.mTask);
    if (task)
        task->onBaseProcCreationFailed(nullptr, true);
}

ActorCreator::~ActorCreator() = default;

bool ActorCreator::requestCreateMapActor(const char* name, sead::Heap* heap,
                                         map::MubinIter* mubin_iter, map::Object* map_object,
                                         BaseProcHandle* handle, int task_lane_id,
                                         InstParamPack* params) {
    const char* actor_profile;
    if (!InfoData::instance()->getActorProfile(&actor_profile, name))
        return false;

    const char* actor_class;
    ActorTemplate::instance()->getActorClass(&actor_class, actor_profile);

    return requestCreateActor_(actor_class, name, heap, mubin_iter, map_object, handle,
                               task_lane_id, params);
}

BaseProc* ActorCreator::createActor_(const char* actor_class, const char* name, sead::Heap* heap,
                                     InstParamPack* params, bool sleep_after_init, bool) {
    auto* debug_heap = util::getDebugHeap();
    bool has_debug_heap = false;
    if (debug_heap && (debug_heap == heap || debug_heap->isInclude(heap))) {
        res::ResourceMgrTask::instance()->controlField9c0d88(false);
        has_debug_heap = true;
    }

    const bool is_high_priority_thread = BaseProcMgr::instance()->isHighPriorityThread();
    SEAD_ASSERT(is_high_priority_thread);

    BaseProcCreateTaskData data;
    data.mHeap = heap;
    data.mProcClass = actor_class;
    data.mProcName = name;
    data.mCreateDelegate = &mCreateProcDelegate;
    data.mSleepAfterInit = sleep_after_init;
    if (params) {
        data.mParams = &params->getBuffer();
        data.mOtherProc = params->getProc();
    }

    BaseProcCreateRequest req;
    req.task_remove_callback = nullptr;
    req.task_lane_id = static_cast<u32>(BaseProcCreateTask::LaneId::_1);
    req.task_data = &data;
    auto* actor = BaseProcMgr::instance()->createProc(req);
    if (has_debug_heap)
        res::ResourceMgrTask::instance()->controlField9c0d88(true);
    return actor;
}

Actor* ActorCreator::createActor(const char* name, sead::Heap* heap, InstParamPack* params,
                                 bool sleep_after_init, bool block_other_synchronous_spawns) {
    BaseProc* proc = nullptr;
    if (block_other_synchronous_spawns)
        mBlockSpawns = true;

    if (block_other_synchronous_spawns || !mBlockSpawns) {
        const char* profile;
        if (InfoData::instance()->getActorProfile(&profile, name)) {
            const char* actor_class;
            ActorTemplate::instance()->getActorClass(&actor_class, profile);
            proc = createActor_(actor_class, name, heap, params, sleep_after_init);
        }
    }

    auto* actor = sead::DynamicCast<Actor>(proc);
    if (!actor && proc)
        proc->deleteLater(BaseProc::DeleteReason::_0);

    return actor;
}

bool ActorCreator::requestCreateActor_(const char* actor_class, const char* name, sead::Heap* heap,
                                       map::MubinIter* mubin_iter, map::Object* map_object,
                                       BaseProcHandle* handle, int task_lane_id,
                                       InstParamPack* params) {
    BaseProcCreateTaskData data;
    data.mHeap = heap;
    data.mProcClass = actor_class;
    data.mProcName = name;
    data.mMubinIter = mubin_iter;
    data.mMapObject = map_object;
    data.mCreateDelegate = &mCreateProcDelegate;
    data.mProcHandle = handle;
    if (params) {
        data.mParams = &params->getBuffer();
        data.mOtherProc = params->getProc();
    }

    BaseProcCreateRequest req;
    req.task_lane_id = task_lane_id;
    req.task_data = &data;
    req.task_remove_callback = &mTaskRemovedDelegate;
    return BaseProcMgr::instance()->requestCreateProc(req);
}

bool ActorCreator::requestCreateActor_(const char* actor_class, const char* name, sead::Heap* heap,
                                       map::Object* map_object, BaseProcHandle* handle,
                                       int task_lane_id, InstParamPack* params) {
    BaseProcCreateTaskData data;
    data.mHeap = heap;
    data.mProcClass = actor_class;
    data.mProcName = name;
    data.mCreateDelegate = &mCreateProcDelegate;
    data.mMapObject = map_object;
    data.mProcHandle = handle;
    if (params) {
        data.mParams = &params->getBuffer();
        data.mOtherProc = params->getProc();
    }

    BaseProcCreateRequest req;
    req.task_lane_id = task_lane_id;
    req.task_data = &data;
    req.task_remove_callback = &mTaskRemovedDelegate;
    return BaseProcMgr::instance()->requestCreateProc(req);
}

bool ActorCreator::requestCreateActor(const char* name, sead::Heap* heap, BaseProcHandle* handle,
                                      InstParamPack* params, map::Object* map_object,
                                      int task_lane_id) {
    const char* actor_profile;
    if (!InfoData::instance()->getActorProfile(&actor_profile, name))
        return false;

    const char* actor_class;
    ActorTemplate::instance()->getActorClass(&actor_class, actor_profile);

    if (mBlockSpawns)
        return false;

    return requestCreateActor_(actor_class, name, heap, map_object, handle, task_lane_id, params);
}

// NON_MATCHING: OffsetList iteration
void ActorCreator::enableDistanceUnloadChecks() {
    const auto lock = sead::makeScopedLock(mActorListCS);
    for (auto it = mActorList.robustBegin(); it != mActorList.robustEnd(); ++it) {
        auto& actor = *it;
        if (!isWeaponOrArmor(&actor) || actor.getProfile().include("ArmorExtra"))
            actor.getActorFlags2().set(Actor::ActorFlag2::NoDistanceCheck);
    }
    mEnableDistanceChecks = true;
}

void ActorCreator::eraseActor(Actor* actor) {
    const auto lock = sead::makeScopedLock(mActorListCS);
    mActorList.erase(actor);
    actor->mCreator = nullptr;
}

void ActorCreator::addScale(InstParamPack& pack, float scale) {
    addScale(pack, {scale, scale, scale});
}

void ActorCreator::addScale(InstParamPack& pack, const sead::Vector3f& scale) {
    sead::SafeString key = "@S";
    pack.getBuffer().add(scale, key);
}

bool ActorCreator::isAITreeParam(const InstParamPack::Entry& entry) {
    return sead::SafeString("=AT") == entry.key;
}

void ActorCreator::addAITreeParam(InstParamPack& pack, const sead::SafeString& value,
                                  const sead::SafeString& name) {
    pack.getBuffer().add(true, "=AT");
    pack.getBuffer().add(value, name);
}

void ActorCreator::addAITreeParam(InstParamPack& pack, int value, const sead::SafeString& name) {
    pack.getBuffer().add(true, "=AT");
    pack.getBuffer().add(value, name);
}

void ActorCreator::addAITreeParam(InstParamPack& pack, u32 value, const sead::SafeString& name) {
    pack.getBuffer().add(true, "=AT");
    pack.getBuffer().add(value, name);
}

void ActorCreator::addAITreeParam(InstParamPack& pack, bool value, const sead::SafeString& name) {
    pack.getBuffer().add(true, "=AT");
    pack.getBuffer().add(value, name);
}

void ActorCreator::setCreatePriorityState1(InstParamPack& pack, BaseProc* proc) {
    pack.setProc(proc);
    proc->setCreatePriorityState1();
}

void ActorCreator::setCreatePriorityState2(InstParamPack& pack, BaseProc* proc) {
    pack.setProc(proc);
    proc->setCreatePriorityState2();
    pack.getBuffer().add(true, "@W");
}

}  // namespace ksys::act
