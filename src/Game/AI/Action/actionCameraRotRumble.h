#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRotRumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRotRumble, ksys::act::ai::Action)
public:
    explicit CameraRotRumble(const InitArg& arg);
    ~CameraRotRumble() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic2_param at offset 0x20
    int* mPattern_d{};
    // dynamic2_param at offset 0x28
    int* mCount_d{};
    // dynamic2_param at offset 0x30
    float* mPower_d{};
};

}  // namespace uking::action
