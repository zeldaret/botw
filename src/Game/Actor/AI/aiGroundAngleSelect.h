#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GroundAngleSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GroundAngleSelect, ksys::act::ai::Ai)
public:
    explicit GroundAngleSelect(const InitArg& arg);
    ~GroundAngleSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSlopeAngle_s{};
    // static_param at offset 0x40
    const bool* mIsCheckEveryFrame_s{};
    // static_param at offset 0x48
    const bool* mIsCheckActorMtx_s{};
};

}  // namespace uking::ai
