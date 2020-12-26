#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRumbleStopWithDamping : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraRumbleStopWithDamping, ksys::act::ai::Action)
public:
    explicit CameraRumbleStopWithDamping(const InitArg& arg);
    ~CameraRumbleStopWithDamping() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic2_param at offset 0x20
    float* mDampingTime_d{};
    // aitree_variable at offset 0x28
    int* mCamVibId_a{};
};

}  // namespace uking::action
