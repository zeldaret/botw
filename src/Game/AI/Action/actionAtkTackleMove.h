#pragma once

#include "Game/AI/Action/actionTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AtkTackleMove : public TackleMove {
    SEAD_RTTI_OVERRIDE(AtkTackleMove, TackleMove)
public:
    explicit AtkTackleMove(const InitArg& arg);
    ~AtkTackleMove() override;

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
