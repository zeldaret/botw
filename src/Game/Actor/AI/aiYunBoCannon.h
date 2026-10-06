#pragma once

#include "Game/Actor/AI/aiBigCannon.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class YunBoCannon : public BigCannon {
    SEAD_RTTI_OVERRIDE(YunBoCannon, BigCannon)
public:
    explicit YunBoCannon(const InitArg& arg);
    ~YunBoCannon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x130
    sead::SafeString mReturnAnchorName_s{};
    // map_unit_param at offset 0x140
    const int* mCannonSpot_m{};
    // map_unit_param at offset 0x148
    sead::SafeString mActorName_m{};
};

}  // namespace uking::ai
