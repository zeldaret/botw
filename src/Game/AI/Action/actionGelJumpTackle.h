#pragma once

#include "Game/AI/Action/actionJumpTackle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GelJumpTackle : public JumpTackle {
    SEAD_RTTI_OVERRIDE(GelJumpTackle, JumpTackle)
public:
    explicit GelJumpTackle(const InitArg& arg);
    ~GelJumpTackle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const int* mSubASSlot_s{};
    // static_param at offset 0xa0
    const float* mBodyRotSpeed_s{};
    // static_param at offset 0xa8
    const bool* mIsEnableCloth_s{};
    // static_param at offset 0xb0
    sead::SafeString mSubAS_s{};
    // static_param at offset 0xc0
    sead::SafeString mLeaveSubAS_s{};
};

}  // namespace uking::action
