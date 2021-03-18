#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class MubinIter;
class Object;
;
}  // namespace ksys::map

namespace ksys::act {

class Actor;
class ActorFactory;
class BaseProc;
struct BaseProcCreateArg;
class BaseProcHandle;

class ActorCreator {
    SEAD_SINGLETON_DISPOSER(ActorCreator)
    ActorCreator();
    virtual ~ActorCreator();

public:
    bool requestCreateMapActor(const char* name, sead::Heap* heap, map::MubinIter* mubin_iter,
                               map::Object* map_object, BaseProcHandle* handle, int task_lane_id,
                               InstParamPack* params);
    Actor* createActor(const char* name, sead::Heap* heap, InstParamPack* params,
                       bool sleep_after_init, bool block_other_synchronous_spawns);
    bool requestCreateActor(const char* name, sead::Heap* heap, BaseProcHandle* handle,
                            InstParamPack* params, map::Object* map_object, int task_lane_id);

    void enableDistanceUnloadChecks();
    void eraseActor(Actor* actor);

    void setActorFactory(ActorFactory* factory) { mActorFactory = factory; }
    bool get5a() const { return _5a; }

    static void addScale(InstParamPack& pack, float scale);
    static void addScale(InstParamPack& pack, const sead::Vector3f& scale);
    static bool isAITreeParam(const InstParamPack::Entry& entry);
    static void addAITreeParam(InstParamPack& pack, const sead::SafeString& value,
                               const sead::SafeString& name);
    static void addAITreeParam(InstParamPack& pack, int value, const sead::SafeString& name);
    static void addAITreeParam(InstParamPack& pack, u32 value, const sead::SafeString& name);
    static void addAITreeParam(InstParamPack& pack, bool value, const sead::SafeString& name);
    static void setCreatePriorityState1(InstParamPack& pack, BaseProc* proc);
    static void setCreatePriorityState2(InstParamPack& pack, BaseProc* proc);

private:
    bool requestCreateActor_(const char* actor_class, const char* name, sead::Heap* heap,
                             map::MubinIter* mubin_iter, map::Object* map_object,
                             BaseProcHandle* handle, int task_lane_id, InstParamPack* params);
    bool requestCreateActor_(const char* actor_class, const char* name, sead::Heap* heap,
                             map::Object* map_object, BaseProcHandle* handle, int task_lane_id,
                             InstParamPack* params);
    BaseProc* createActor_(const char* actor_class, const char* name, sead::Heap* heap,
                           InstParamPack* params, bool sleep_after_init, bool = false);

    BaseProc* doCreateProc(BaseProcCreateArg& arg);
    void onTaskRemoved(const util::TaskRemoveCallbackContext& context);

    sead::Heap* mForBaseProcDualHeap;
    sead::Heap* mPlacementMgrHeap;
    sead::OffsetList<Actor> mActorList;
    void* _50{};
    bool mEnableDistanceChecks;
    bool mBlockSpawns;
    bool _5a;
    void* _60{};
    sead::Delegate1R<ActorCreator, BaseProcCreateArg&, BaseProc*> mCreateProcDelegate{
        this, &ActorCreator::doCreateProc};
    util::TaskRemoveCallbackT<ActorCreator> mTaskRemovedDelegate{this,
                                                                 &ActorCreator::onTaskRemoved};
    sead::CriticalSection mActorListCS;
    ActorFactory* mActorFactory;
};
KSYS_CHECK_SIZE_NX150(ActorCreator, 0xf0);

}  // namespace ksys::act
