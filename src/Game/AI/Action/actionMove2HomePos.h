#pragma once

#include "Game/AI/Action/actionMove2HomePosBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Move2HomePos : public Move2HomePosBase {
    SEAD_RTTI_OVERRIDE(Move2HomePos, Move2HomePosBase)
public:
    explicit Move2HomePos(const InitArg& arg);
    ~Move2HomePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const sead::Vector3f* mVibDirection_s{};
    // static_param at offset 0x58
    const int* mVibPattern_s{};
    // static_param at offset 0x60
    const float* mVibPower_s{};
    // static_param at offset 0x68
    const float* mVibRange_s{};
    // static_param at offset 0x70
    const bool* mIsVibration_s{};
};

}  // namespace uking::action
