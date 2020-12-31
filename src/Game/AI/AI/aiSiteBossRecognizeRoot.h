#pragma once

#include "Game/AI/AI/aiSiteBossRecognizeRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossRecognizeRoot : public SiteBossRecognizeRootBase {
    SEAD_RTTI_OVERRIDE(SiteBossRecognizeRoot, SiteBossRecognizeRootBase)
public:
    explicit SiteBossRecognizeRoot(const InitArg& arg);
    ~SiteBossRecognizeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mIgnoreWaprDistMax_s{};
    // static_param at offset 0x70
    const bool* mIsCheckChildDevice_s{};
    // static_param at offset 0x78
    const bool* mIgnoreWarpDistRetFromDamage_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mChaseDistOffset_s{};
};

}  // namespace uking::ai
