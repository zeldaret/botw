#pragma once

#include "Game/AI/Action/actionWaitBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KeepPosInWater : public WaitBase {
    SEAD_RTTI_OVERRIDE(KeepPosInWater, WaitBase)
public:
    explicit KeepPosInWater(const InitArg& arg);
    ~KeepPosInWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const float* mForceTurnLimitSpeedStream_s{};
    // static_param at offset 0x58
    const float* mChaceFrontRate_s{};
    // static_param at offset 0x60
    const float* mChaceAngSpeedMax_s{};
    // static_param at offset 0x68
    sead::SafeString mASKeyName_s{};
};

}  // namespace uking::action
