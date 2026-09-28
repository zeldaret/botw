#pragma once

#include "Game/Actor/Action/actionHorseRideBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideLookWait : public HorseRideBase {
    SEAD_RTTI_OVERRIDE(HorseRideLookWait, HorseRideBase)
public:
    explicit HorseRideLookWait(const InitArg& arg);
    ~HorseRideLookWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mRotRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
