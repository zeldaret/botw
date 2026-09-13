#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearNearTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AppearNearTarget, ksys::act::ai::Ai)
public:
    explicit AppearNearTarget(const InitArg& arg);
    ~AppearNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDist_s{};
    // static_param at offset 0x40
    const float* mTeraDist_s{};
    // map_unit_param at offset 0x48
    const int* mNearCreateAppearID_m{};
    // aitree_variable at offset 0x50
    bool* mIsStopFallCheck_a{};
};

}  // namespace uking::ai
