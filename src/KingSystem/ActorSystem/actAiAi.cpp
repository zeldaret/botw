#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace ksys::act::ai {

Ai::Ai(const ActionBase::InitArg& arg) : ActionBase(arg) {}

Ai::~Ai() {
    mChildren.freeBuffer();
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

template class ClassContainer<Ai>;

}  // namespace ksys::act::ai
