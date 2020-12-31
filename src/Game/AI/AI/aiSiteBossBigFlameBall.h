#pragma once

#include "Game/AI/AI/aiSiteBossFlameBall.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossBigFlameBall : public SiteBossFlameBall {
    SEAD_RTTI_OVERRIDE(SiteBossBigFlameBall, SiteBossFlameBall)
public:
    explicit SiteBossBigFlameBall(const InitArg& arg);
    ~SiteBossBigFlameBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d0
    const sead::Vector3f* mDestOffset_s{};
    // static_param at offset 0x1d8
    const sead::Vector3f* mDestOffset1_s{};
    // map_unit_param at offset 0x1e0
    const float* mSpeed_m{};
    // map_unit_param at offset 0x1e8
    const sead::Vector3f* mRotOffset_m{};
};

}  // namespace uking::ai
