#include "KingSystem/ActorSystem/actAiAction.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actionDummyAction.h"
#include "KingSystem/Resource/resResourceAIProgram.h"

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
    for (s32 i = 0; i < classes.size(); ++i) {
        if (classes[i]) {
            delete classes[i];
            classes[i] = nullptr;
        }
    }

    predelete1_callbacks.freeBuffer();
    predelete2_callbacks.freeBuffer();
    classes.freeBuffer();
}

bool Actions::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_actions = aiprog->getActions().size();
    if (num_actions == 0)
        return true;

    if (!classes.tryAllocBuffer(num_actions, heap))
        return false;
    for (s32 i = 0; i < num_actions; ++i)
        classes(i) = nullptr;
    auto it_class = classes.begin();
    const auto it_class_end = classes.end();

    Action::InitArg arg{};
    arg.actor = actor;
    arg.def_idx = -1;
    arg.root_idx = -1;
    s32 predelete1_callback_num = 0;
    s32 predelete2_callback_num = 0;
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

        predelete2_callback_num += (*it_class)->m8();
        predelete1_callback_num += (*it_class)->m7();
    }

    // Allocate the callback lists.
    if (predelete1_callback_num != 0) {
        if (!predelete1_callbacks.tryAllocBuffer(predelete1_callback_num, heap))
            return false;
        for (s32 i = 0; i < predelete1_callback_num; ++i)
            predelete1_callbacks(i) = nullptr;
    }

    if (predelete2_callback_num != 0) {
        if (!predelete2_callbacks.tryAllocBuffer(predelete2_callback_num, heap))
            return false;
        for (s32 i = 0; i < predelete2_callback_num; ++i)
            predelete2_callbacks(i) = nullptr;
    }

    // Initialize each class.
    s32 idx_cb1 = 0, idx_cb2 = 0;
    for (auto it = classes.begin(), end = classes.end(); it != end; ++it) {
        if (!(*it)->init(heap, false))
            return false;

        if ((*it)->m8()) {
            predelete2_callbacks[idx_cb2] = *it;
            ++idx_cb2;
        }

        if ((*it)->m7()) {
            predelete1_callbacks[idx_cb1] = *it;
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

bool Actions::onActorPreDelete2() const {
    bool ok = true;
    for (auto* action : predelete2_callbacks) {
        if (action)
            ok &= action->m18();
    }
    return ok;
}

void Actions::onActorPreDelete1() const {
    for (auto* action : predelete1_callbacks) {
        if (action)
            action->m19();
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

}  // namespace ksys::act::ai
