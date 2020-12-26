#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRumbleLoop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRumbleLoop, ksys::act::ai::Action)
public:
    explicit CameraRumbleLoop(const InitArg& arg);
    ~CameraRumbleLoop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

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
