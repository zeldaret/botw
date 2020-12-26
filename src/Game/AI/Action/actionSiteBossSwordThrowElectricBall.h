#pragma once

#include "Game/AI/Action/actionSiteBossThrowParts.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordThrowElectricBall : public SiteBossThrowParts {
    SEAD_RTTI_OVERRIDE(SiteBossSwordThrowElectricBall, SiteBossThrowParts)
public:
    explicit SiteBossSwordThrowElectricBall(const InitArg& arg);
    ~SiteBossSwordThrowElectricBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const float* mMoveSpeed_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mMoveOffset_s{};
};

}  // namespace uking::action
