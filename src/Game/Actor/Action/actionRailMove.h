#pragma once

#include "Game/Actor/Action/actionDestPointMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RailMove : public DestPointMoveBase {
    SEAD_RTTI_OVERRIDE(RailMove, DestPointMoveBase)
public:
    explicit RailMove(const InitArg& arg);
    ~RailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    sead::SafeString mRailName_d{};
};

}  // namespace uking::action
