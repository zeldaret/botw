#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include <thread/seadCriticalSection.h>

namespace ksys::act {

class Actor;
struct ActorCreateArg;
class ActorFactory;

class ActorCreator {
    SEAD_SINGLETON_DISPOSER(ActorCreator)
    ActorCreator();
    virtual ~ActorCreator();

public:
    void setActorFactory(ActorFactory* factory) { mActorFactory = factory; }

    bool get5a() const { return _5a; }

private:
    sead::Heap* forBaseProcDualHeap;
    sead::Heap* placementMgrHeap;
    sead::OffsetList<Actor> mActorList;
    void* _50;
    bool mEnableDistanceChecks;
    bool _59;
    bool _5a;
    void* _60;
    sead::Delegate1<ActorCreator, ActorCreateArg&> mCreateActorDelegate;
    // FIXME: argument type
    sead::Delegate1<ActorCreator, void*> mCleanUpDelegate;
    sead::CriticalSection mActorListCS;
    ActorFactory* mActorFactory;
};

}  // namespace ksys::act
