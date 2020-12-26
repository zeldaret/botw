#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuCommonDownTimer : public Fork {
    SEAD_RTTI_OVERRIDE(ChuchuCommonDownTimer, Fork)
public:
    explicit ChuchuCommonDownTimer(const InitArg& arg);
    ~ChuchuCommonDownTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mMinWaitFrame_s{};
    // aitree_variable at offset 0x38
    int* mChemicalChuchuCommonDownTime_a{};
};

}  // namespace uking::action
