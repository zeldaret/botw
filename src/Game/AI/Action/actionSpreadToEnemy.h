#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SpreadToEnemy : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(SpreadToEnemy, OnetimeStopASPlay)
public:
    explicit SpreadToEnemy(const InitArg& arg);
    ~SpreadToEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mSpreadDist_s{};
};

}  // namespace uking::action
