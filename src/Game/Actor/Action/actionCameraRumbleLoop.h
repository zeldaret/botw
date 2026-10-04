#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRumbleLoop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRumbleLoop, ksys::act::ai::Action)
public:
    explicit CameraRumbleLoop(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic2_param at offset 0x20
    int* mPattern_d{};
    // dynamic2_param at offset 0x28
    float* mPower_d{};
    // dynamic2_param at offset 0x30
    bool* mSideways_d{};
    // aitree_variable at offset 0x38
    int* mCamVibId_a{};
};

}  // namespace uking::action
