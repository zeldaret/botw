#pragma once

#include "Game/Actor/Action/actionTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TackleAttack : public TackleMove {
    SEAD_RTTI_OVERRIDE(TackleAttack, TackleMove)
public:
    explicit TackleAttack(const InitArg& arg);
    ~TackleAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    sead::SafeString mAtkSensorName_s{};
};

}  // namespace uking::action
