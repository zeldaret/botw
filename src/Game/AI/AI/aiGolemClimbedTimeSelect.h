#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemClimbedTimeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemClimbedTimeSelect, ksys::act::ai::Ai)
public:
    explicit GolemClimbedTimeSelect(const InitArg& arg);
    ~GolemClimbedTimeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLimitTime_s{};
    // aitree_variable at offset 0x40
    float* mGolemClimbedTime_a{};
};

}  // namespace uking::ai
