#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EmitElectricWaterBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EmitElectricWaterBall, ksys::act::ai::Action)
public:
    explicit EmitElectricWaterBall(const InitArg& arg);
    ~EmitElectricWaterBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mActorName_s{};
};

}  // namespace uking::action
