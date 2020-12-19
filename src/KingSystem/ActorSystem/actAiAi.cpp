#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
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

}  // namespace ksys::act::ai
