#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FreeMove, ksys::act::ai::Action)
public:
    explicit FreeMove(const InitArg& arg);
    ~FreeMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x40];
    // static_param at offset 0x60
    const float* mSpeed_s{};
    // static_param at offset 0x68
    const float* mSpeedAddRate_s{};
    // static_param at offset 0x70
    const float* mAngleSpeed_s{};
    // static_param at offset 0x78
    const bool* mIsChangeable_s{};
    // static_param at offset 0x80
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x88
    const bool* mAllowPitchRotation_s{};
    // static_param at offset 0x90
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action
