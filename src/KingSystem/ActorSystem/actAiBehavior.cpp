#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/behaviorDummyBehavior.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace ksys::act::ai {

Behavior::Behavior(const InitArg& arg)
    : mActor(arg.actor), mDefIdx(static_cast<u16>(arg.def_idx)) {}

Behaviors::Behaviors() = default;

Behaviors::~Behaviors() {
    finalize();
}

void Behaviors::finalize() {
    for (s32 i = 0; i < mClasses.size(); ++i) {
        if (mClasses[i]) {
            delete mClasses[i];
            mClasses[i] = nullptr;
        }
    }

    mOnPreDeleteCbs.freeBuffer();
    mUpdateForPreDeleteCbs.freeBuffer();
    mClasses.freeBuffer();
}

bool Behaviors::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_behaviors = aiprog->getBehaviors().size();
    if (num_behaviors == 0)
        return true;

    if (!mClasses.tryAllocBuffer(num_behaviors, heap))
        return false;
    for (s32 i = 0, n = mClasses.size(); i != n; ++i)
        mClasses(i) = nullptr;
    auto it_class = mClasses.begin();
    const auto it_class_end = mClasses.end();

    Behavior::InitArg arg;
    arg.actor = actor;
    s32 predelete_cb_num = 0;
    s32 update_cb_num = 0;
    for (; it_class != it_class_end; ++it_class) {
        arg.def_idx = it_class.getIndex();
        const char* name = aiprog->getBehaviors()[it_class.getIndex()].mClassName;

        auto* factory = getFactory(name);
        if (factory)
            *it_class = factory->create_fn(arg, heap);
        else
            *it_class = new (heap) DummyBehavior(arg);

        if (!*it_class)
            return false;

        update_cb_num += (*it_class)->hasUpdateForPreDeleteCb();
        predelete_cb_num += (*it_class)->hasPreDeleteCb();
    }

    // Allocate the callback lists.
    if (predelete_cb_num != 0) {
        if (!mOnPreDeleteCbs.tryAllocBuffer(predelete_cb_num, heap))
            return false;
        for (s32 i = 0; i < predelete_cb_num; ++i)
            mOnPreDeleteCbs(i) = nullptr;
    }

    if (update_cb_num != 0) {
        if (!mUpdateForPreDeleteCbs.tryAllocBuffer(update_cb_num, heap))
            return false;
        for (s32 i = 0; i < update_cb_num; ++i)
            mUpdateForPreDeleteCbs(i) = nullptr;
    }

    // Initialize each class.
    s32 idx_cb1 = 0, idx_cb2 = 0;
    for (auto it = mClasses.begin(), end = mClasses.end(); it != end; ++it) {
        if (!(*it)->init(heap))
            return false;

        if ((*it)->hasUpdateForPreDeleteCb()) {
            mUpdateForPreDeleteCbs[idx_cb2] = *it;
            ++idx_cb2;
        }

        if ((*it)->hasPreDeleteCb()) {
            mOnPreDeleteCbs[idx_cb1] = *it;
            ++idx_cb1;
        }
    }

    return true;
}

bool Behaviors::updateForPreDelete() const {
    bool ok = true;
    for (auto* cb : mUpdateForPreDeleteCbs) {
        if (cb)
            ok &= cb->updateForPreDelete();
    }
    return ok;
}

void Behaviors::onPreDelete() const {
    for (auto* cb : mOnPreDeleteCbs) {
        if (cb)
            cb->onPreDelete();
    }
}

BehaviorFactory* Behaviors::getFactory(const sead::SafeString& name) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const s32 idx = sFactories.binarySearch(
        name_hash, +[](const BehaviorFactory& factory, const u32& hash) {
            if (factory.hash < hash)
                return -1;
            if (factory.hash > hash)
                return 1;
            return 0;
        });
    if (idx < 0)
        return nullptr;
    return sFactories.get(idx);
}

void Behaviors::setFactories(int count, BehaviorFactory* factories) {
    sFactories.setBuffer(count, factories);
}

}  // namespace ksys::act::ai
