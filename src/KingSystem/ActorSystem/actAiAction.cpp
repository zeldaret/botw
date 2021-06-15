#include "KingSystem/ActorSystem/actAiAction.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actionDummyAction.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"

namespace ksys::act::ai {

Action::Action(const InitArg& arg) : ActionBase(arg) {}

void Action::calc() {
    calc_();
}

Actions::Actions() = default;

Actions::~Actions() {
    finalize();
}

void Actions::finalize() {
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

bool Actions::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_actions = aiprog->getActions().size();
    if (num_actions == 0)
        return true;

    if (!mClasses.tryAllocBuffer(num_actions, heap))
        return false;
    for (s32 i = 0; i < num_actions; ++i)
        mClasses(i) = nullptr;
    auto it_class = mClasses.begin();
    const auto it_class_end = mClasses.end();

    Action::InitArg arg{};
    arg.actor = actor;
    arg.def_idx = -1;
    arg.root_idx = -1;
    s32 pre_delete_cb_num = 0;
    s32 update_cb_num = 0;
    for (; it_class != it_class_end; ++it_class) {
        const char* name;
        if (it_class.getIndex() >= num_actions) {
            arg.root_idx = it_class.getIndex() - num_actions;
            arg.def_idx = -1;
            name = getDefaultActionName(arg.root_idx);
        } else {
            arg.def_idx = it_class.getIndex();
            name = aiprog->getActions()[it_class.getIndex()].mClassName;
        }

        auto* factory = getFactory(name);
        if (factory)
            *it_class = factory->create_fn(arg, heap);
        else
            *it_class = new (heap) DummyAction(arg);

        if (!*it_class)
            return false;

        update_cb_num += (*it_class)->hasUpdateForPreDeleteCb();
        pre_delete_cb_num += (*it_class)->hasPreDeleteCb();
    }

    // Allocate the callback lists.
    if (pre_delete_cb_num != 0) {
        if (!mOnPreDeleteCbs.tryAllocBuffer(pre_delete_cb_num, heap))
            return false;
        for (s32 i = 0; i < pre_delete_cb_num; ++i)
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
        if (!(*it)->init(heap, false))
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

Action* Actions::clone(const Action& action, sead::Heap* heap) {
    auto* factory = getFactory(action.getClassName());
    if (!factory)
        return nullptr;

    Action::InitArg arg;
    arg.actor = action.getActor();
    arg.def_idx = action.getDefinitionIdx();
    auto* clone = factory->create_fn(arg, heap);
    if (!clone) {
        return nullptr;
    }
    if (!clone->init(heap, true)) {
        delete clone;
        return nullptr;
    }
    return clone;
}

bool Actions::updateForPreDelete() const {
    bool ok = true;
    for (auto* action : mUpdateForPreDeleteCbs) {
        if (action)
            ok &= action->updateForPreDelete();
    }
    return ok;
}

void Actions::onPreDelete() const {
    for (auto* action : mOnPreDeleteCbs) {
        if (action)
            action->onPreDelete();
    }
}

ActionFactory* Actions::getFactory(const sead::SafeString& name) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const s32 idx = sFactories.binarySearch(
        name_hash, +[](const ActionFactory& factory, const u32& hash) {
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

void Actions::setFactories(int count, ActionFactory* factories) {
    sFactories.setBuffer(count, factories);
}

sead::Buffer<ActionFactory> Actions::sFactories;

}  // namespace ksys::act::ai
