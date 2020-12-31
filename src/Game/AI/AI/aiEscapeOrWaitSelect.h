#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EscapeOrWaitSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EscapeOrWaitSelect, ksys::act::ai::Ai)
public:
    explicit EscapeOrWaitSelect(const InitArg& arg);
    ~EscapeOrWaitSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mEscapeRange_s{};
    // static_param at offset 0x40
    const float* mEscapeMoveDistMin_s{};
    // static_param at offset 0x48
    const float* mEscapeMoveDistMax_s{};
    // static_param at offset 0x50
    const float* mCheckBackAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
