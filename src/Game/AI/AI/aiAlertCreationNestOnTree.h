#pragma once

#include "Game/AI/AI/aiCreationNestOnTree.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AlertCreationNestOnTree : public CreationNestOnTree {
    SEAD_RTTI_OVERRIDE(AlertCreationNestOnTree, CreationNestOnTree)
public:
    explicit AlertCreationNestOnTree(const InitArg& arg);
    ~AlertCreationNestOnTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1f8
    const int* mCreateIntervalTime_s{};
};

}  // namespace uking::ai
