#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokPotRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokPotRootAI, ksys::act::ai::Ai)
public:
    explicit KorokPotRootAI(const InitArg& arg);
    ~KorokPotRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCrayLaunchSpeedRate_s{};
    // static_param at offset 0x40
    const float* mCrayLaunchAngularSpeed_s{};
    // map_unit_param at offset 0x48
    const float* mCrayLaunchSpeed_m{};
    // map_unit_param at offset 0x50
    const bool* mIsCrayShot_m{};
};

}  // namespace uking::ai
