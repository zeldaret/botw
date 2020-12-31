#pragma once

#include "Game/AI/AI/aiAncientNecklaceBallBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AncientNecklaceBall : public AncientNecklaceBallBase {
    SEAD_RTTI_OVERRIDE(AncientNecklaceBall, AncientNecklaceBallBase)
public:
    explicit AncientNecklaceBall(const InitArg& arg);
    ~AncientNecklaceBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x100
    const float* mLandNoiseLevel_s{};
    // map_unit_param at offset 0x108
    const int* mGrabNodeIndex_m{};
    // map_unit_param at offset 0x110
    sead::SafeString mGiantNecklaceActiveSaveFlag_m{};
};

}  // namespace uking::ai
