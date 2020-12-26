#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAITreeValWeakPointTimer : public Fork {
    SEAD_RTTI_OVERRIDE(ForkAITreeValWeakPointTimer, Fork)
public:
    explicit ForkAITreeValWeakPointTimer(const InitArg& arg);
    ~ForkAITreeValWeakPointTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mTimer_s{};
    // aitree_variable at offset 0x38
    void* mWeakPointCounter_a{};
};

}  // namespace uking::action
