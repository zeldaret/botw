#pragma once

#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianBeamFire : public BeamMove {
    SEAD_RTTI_OVERRIDE(GuardianBeamFire, BeamMove)
public:
    explicit GuardianBeamFire(const InitArg& arg);
    ~GuardianBeamFire() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mSpeed_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mEyePos_d{};
};

}  // namespace uking::action
