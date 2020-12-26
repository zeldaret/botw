#pragma once

#include "Game/AI/Action/actionTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NoAtTackleMove : public TackleMove {
    SEAD_RTTI_OVERRIDE(NoAtTackleMove, TackleMove)
public:
    explicit NoAtTackleMove(const InitArg& arg);
    ~NoAtTackleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    sead::SafeString mAS_s{};
};

}  // namespace uking::action
