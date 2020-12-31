#pragma once

#include "Game/AI/AI/aiCommonPickedItem.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TreasureSpot : public CommonPickedItem {
    SEAD_RTTI_OVERRIDE(TreasureSpot, CommonPickedItem)
public:
    explicit TreasureSpot(const InitArg& arg);
    ~TreasureSpot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe8
    sead::SafeString mGetAttKeyForGuardian_s{};
    // map_unit_param at offset 0xf8
    const int* mTresasureSpotType_m{};
};

}  // namespace uking::ai
