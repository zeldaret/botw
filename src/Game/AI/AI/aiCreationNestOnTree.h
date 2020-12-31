#pragma once

#include "Game/AI/AI/aiItemOnTree.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CreationNestOnTree : public ItemOnTree {
    SEAD_RTTI_OVERRIDE(CreationNestOnTree, ItemOnTree)
public:
    explicit CreationNestOnTree(const InitArg& arg);
    ~CreationNestOnTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb8
    const int* mActorNum_s{};
    // static_param at offset 0xc0
    const float* mTargetEscapedRadius_s{};
    // static_param at offset 0xc8
    const bool* mIsRemainNum_s{};
};

}  // namespace uking::ai
