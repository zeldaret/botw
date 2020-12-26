#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class VacuumedItemShootToTarget : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(VacuumedItemShootToTarget, OnetimeStopASPlay)
public:
    explicit VacuumedItemShootToTarget(const InitArg& arg);
    ~VacuumedItemShootToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf0
    const bool* mIsReuseBullet_s{};
};

}  // namespace uking::action
