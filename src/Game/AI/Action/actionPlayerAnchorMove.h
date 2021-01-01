#pragma once

#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerAnchorMove : public PlayerGuidedMove {
    SEAD_RTTI_OVERRIDE(PlayerAnchorMove, PlayerGuidedMove)
public:
    explicit PlayerAnchorMove(const InitArg& arg);
    ~PlayerAnchorMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x68
    sead::SafeString mAnchorName_d{};
};

}  // namespace uking::action
