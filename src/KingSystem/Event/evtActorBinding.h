#pragma once

#include <container/seadPtrArray.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>

namespace evfl {
struct ResAction;
struct ResActor;
struct ResQuery;
}  // namespace evfl

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class ActorBindings;

class ActorBinding {
public:
    // TODO: rename these values after figuring out what they do
    SEAD_ENUM(ActorCreateMode, k0, k1, k2, k3, k4, k5, k6, k7, k8)

    ActorBinding(const evfl::ResActor* res, ActorBindings* parent)
        : mResActor(res), mParent(parent) {}

    void bindAction(const evfl::ResAction* action);
    void bindQuery(const evfl::ResQuery* query);

    sead::SafeString getActorName() const;
    sead::SafeString getActorSubName() const;
    ActorCreateMode getActorCreateMode(const act::Actor* actor) const;

    const evfl::ResActor* getRes() const { return mResActor; }
    const sead::PtrArray<const evfl::ResAction>& getActions() const { return mActions; }
    const sead::PtrArray<const evfl::ResQuery>& getQueries() const { return mQueries; }
    ActorBindings* getParent() const { return mParent; }

    void allocActions(sead::Heap* heap) {
        if (mNumActionsToAlloc > 0)
            mActions.allocBuffer(mNumActionsToAlloc, heap);
    }

    void allocQueries(sead::Heap* heap) {
        if (mNumQueriesToAlloc > 0)
            mQueries.allocBuffer(mNumQueriesToAlloc, heap);
    }

    void finalize() {
        if (mActions.isBufferReady())
            mActions.freeBuffer();
        if (mQueries.isBufferReady())
            mQueries.freeBuffer();
    }

private:
    const evfl::ResActor* mResActor = nullptr;
    sead::PtrArray<const evfl::ResAction> mActions;
    sead::PtrArray<const evfl::ResQuery> mQueries;
    ActorBindings* mParent = nullptr;
    int _30 = 0;
    int mNumActionsToAlloc = 0;
    int mNumQueriesToAlloc = 0;
    bool _3c = false;
};

}  // namespace ksys::evt
