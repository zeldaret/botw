#pragma once

#include "Game/AI/Action/actionTimeredASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BurnDamage : public TimeredASPlay {
    SEAD_RTTI_OVERRIDE(BurnDamage, TimeredASPlay)
public:
    explicit BurnDamage(const InitArg& arg);
    ~BurnDamage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
