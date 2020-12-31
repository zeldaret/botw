#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HeightSelectTwoAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HeightSelectTwoAction, ksys::act::ai::Ai)
public:
    explicit HeightSelectTwoAction(const InitArg& arg);
    ~HeightSelectTwoAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSelectCheckInterval_s{};
    // static_param at offset 0x40
    const float* mHeightMin_s{};
    // static_param at offset 0x48
    const float* mHeightMax_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
