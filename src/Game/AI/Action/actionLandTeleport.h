#pragma once

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LandTeleport : public TeleportBase {
    SEAD_RTTI_OVERRIDE(LandTeleport, TeleportBase)
public:
    explicit LandTeleport(const InitArg& arg);
    ~LandTeleport() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mDistXZ_s{};
    // static_param at offset 0x80
    const float* mDistY_s{};
    // static_param at offset 0x88
    const float* mSearchClosestPointRadius_s{};
    // static_param at offset 0x90
    const bool* mIsNormalizeAxisY_s{};
};

}  // namespace uking::action
