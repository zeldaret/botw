#pragma once

#include "Game/AI/Action/actionWarpPlayerBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayer : public WarpPlayerBase {
    SEAD_RTTI_OVERRIDE(WarpPlayer, WarpPlayerBase)
public:
    explicit WarpPlayer(const InitArg& arg);
    ~WarpPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    sead::SafeString mWarpDestMapName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mWarpDestPosName_d{};
};

}  // namespace uking::action
