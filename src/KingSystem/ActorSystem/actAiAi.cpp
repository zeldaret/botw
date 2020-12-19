#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/aiDummyAi.h"
#include "KingSystem/Resource/resResourceAIProgram.h"

namespace ksys::act::ai {

inline res::AIProgram* ActionBase::getAIProg() const {
    return mActor->getParam()->getRes().mAIProgram;
}

Ai::Ai(const ActionBase::InitArg& arg) : ActionBase(arg) {}

Ai::~Ai() {
    mChildren.freeBuffer();
}

bool Ai::initChildren(const AIDefSet& set, sead::Heap* heap) {
    if (set.num_children > 0) {
        if (mDefinitionIdx < 0)
            return false;

        auto indices = getAIProg()->getAI(mDefinitionIdx).mChildIndices;
        if (!initChildren_(set.num_children, nullptr, indices, heap))
            return false;
    }
    return true;
}

bool Ai::initChildren_(s32 num_children, const char** names, sead::Buffer<u16>& indices,
                       sead::Heap* heap) {
    auto* actor = mActor;

    if (indices.size() != num_children && !isPlayerProfile(actor) && !isCameraProfile(actor))
        return false;

    if (num_children <= 0)
        return false;

    if (!mChildren.tryAllocBuffer(num_children, heap))
        return false;

    for (s32 i = 0; i < num_children; ++i)
        mChildren(i) = nullptr;

    auto* root_ai = actor->getRootAi();

    const auto num_ais = actor->getParam()->getRes().mAIProgram->getAIs().size();
    const bool is_root_ai = sead::IsDerivedFrom<RootAi>(this);
    const auto effective_ai_count = is_root_ai + num_ais;

    auto it_idx = indices.begin();
    auto it_ptr = mChildren.begin();
    const auto it_idx_end = indices.end();
    const auto it_ptr_end = mChildren.end();

    for (; it_ptr != it_ptr_end && it_idx != it_idx_end; ++it_ptr, ++it_idx) {
        if (*it_idx < effective_ai_count)
            *it_ptr = root_ai->getAis().classes[*it_idx];
        else
            *it_ptr = root_ai->getActions().classes[*it_idx - effective_ai_count];

        if (*it_ptr == nullptr)
            return false;
    }
    return true;
}

void Ai::calc() {
    calc_();

    auto* child = getCurrentChild();
    if (child)
        child->calc();

    if (mPendingChildIdx != InvalidIdx && mChildIdx != mPendingChildIdx) {
        handlePendingChildChange_();
        auto* new_child = getCurrentChild();
        if (new_child)
            new_child->calc();
    }
}

bool Ai::isFlag4Set() const {
    auto* child = getCurrentChild();
    if (child)
        return child->isFlag4Set();

    return mFlags.isOn(Flag::_4);
}

ActionBase* Ai::getCurrentChild() const {
    if (mChildIdx == InvalidIdx)
        return nullptr;
    return mChildren[mChildIdx];
}

void Ai::updateChildIdx(u16 new_idx) {
    const auto prev_idx = mChildIdx;
    mChildIdx = new_idx;
    mPrevChildIdx = prev_idx;
    mPendingChildIdx = InvalidIdx;
}

Ais::Ais() = default;

Ais::~Ais() {
    finalize();
}

void Ais::finalize() {
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

bool Ais::init(Actor* actor, sead::Heap* heap) {
    const auto* aiprog = actor->getParam()->getRes().mAIProgram;

    const auto num_ais = aiprog->getAIs().size();
    if (num_ais < 0)
        return false;

    if (!classes.tryAllocBuffer(num_ais + 1, heap))
        return false;
    for (s32 i = 0, n = classes.size(); i != n; ++i)
        classes(i) = nullptr;
    auto it_class = classes.begin();
    const auto it_class_end = classes.end();

    Ai::InitArg arg{};
    arg.actor = actor;
    arg.def_idx = -1;
    arg.root_idx = -1;
    s32 predelete1_callback_num = 0;
    s32 predelete2_callback_num = 0;
    for (; it_class != it_class_end; ++it_class) {
        const char* name;
        if (it_class.getIndex() >= num_ais) {
            arg.root_idx = it_class.getIndex() - num_ais;
            arg.def_idx = -1;
            name = getDefaultAiName(arg.root_idx);
        } else {
            arg.def_idx = it_class.getIndex();
            name = aiprog->getAIs()[it_class.getIndex()].mClassName;
        }

        auto* factory = getFactory(name);
        if (factory)
            *it_class = factory->create_fn(arg, heap);
        else
            *it_class = new (heap) DummyAi(arg);

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

    for (auto* ai : classes) {
        if (!ai->gatherParamsFromChildren(heap))
            return false;
    }

    return true;
}

Ai* Ais::clone(const Ai& action, sead::Heap* heap) {
    auto* factory = getFactory(action.getClassName());
    if (!factory)
        return nullptr;

    Ai::InitArg arg;
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

bool Ais::onActorPreDelete2() const {
    bool ok = true;
    for (auto* action : predelete2_callbacks) {
        if (action)
            ok &= action->m18();
    }
    return ok;
}

void Ais::onActorPreDelete1() const {
    for (auto* action : predelete1_callbacks) {
        if (action)
            action->m19();
    }
}

AiFactory* Ais::getFactory(const sead::SafeString& name) {
    const u32 name_hash = sead::HashCRC32::calcStringHash(name);
    const s32 idx = sFactories.binarySearch(
        name_hash, +[](const AiFactory& factory, const u32& hash) {
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

void Ais::setFactories(int count, AiFactory* factories) {
    sFactories.setBuffer(count, factories);
}

}  // namespace ksys::act::ai
