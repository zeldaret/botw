#pragma once

#include "Game/Actor/Action/actionDestPlayerWarpBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayer : public DestPlayerWarpBase {
    SEAD_RTTI_OVERRIDE(WarpPlayer, DestPlayerWarpBase)
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
