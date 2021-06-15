#include "KingSystem/ActorSystem/actAiQueries.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/ActorSystem/queryDummyQuery.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace ksys::act::ai {

Queries::Queries() = default;

Queries::~Queries() {
    finalize();
}

void Queries::finalize() {
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

bool Queries::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_Queries = aiprog->getQueries().size();
    if (num_Queries == 0)
        return true;

    if (!mClasses.tryAllocBuffer(num_Queries, heap))
        return false;
    for (s32 i = 0, n = mClasses.size(); i != n; ++i)
        mClasses(i) = nullptr;
    auto it_class = mClasses.begin();
    const auto it_class_end = mClasses.end();

    Query::InitArg arg;
    arg.actor = actor;
    s32 predelete_cb_num = 0;
    s32 update_cb_num = 0;
    for (; it_class != it_class_end; ++it_class) {
        arg.def_idx = it_class.getIndex();
        const char* name = aiprog->getQueries()[it_class.getIndex()].mClassName;

        auto* factory = getFactory(name);
        if (factory)
            *it_class = factory->create_fn(arg, heap);
        else
            *it_class = new (heap) DummyQuery(arg);

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

bool Queries::updateForPreDelete() const {
    bool ok = true;
    for (auto* cb : mUpdateForPreDeleteCbs) {
        if (cb)
            ok &= cb->updateForPreDelete();
    }
    return ok;
}

void Queries::onPreDelete() const {
    for (auto* cb : mOnPreDeleteCbs) {
        if (cb)
            cb->onPreDelete();
    }
}

Query* Queries::getQuery(const sead::SafeString& name) const {
    for (auto* query : mClasses) {
        if (name == query->getName())
            return query;
    }
    return nullptr;
}

QueryFactory* Queries::getFactory(const sead::SafeString& name) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const s32 idx = sFactories.binarySearch(
        name_hash, +[](const QueryFactory& factory, const u32& hash) {
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

void Queries::setFactories(int count, QueryFactory* factories) {
    sFactories.setBuffer(count, factories);
}

sead::Buffer<QueryFactory> Queries::sFactories;

}  // namespace ksys::act::ai
