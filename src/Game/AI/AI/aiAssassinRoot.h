#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(AssassinRoot, NPCRoot)
public:
    explicit AssassinRoot(const InitArg& arg);
    ~AssassinRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x238
    const float* mChangeDistance_s{};
    // map_unit_param at offset 0x240
    sead::SafeString mEquipItem1_m{};
    // map_unit_param at offset 0x250
    sead::SafeString mEquipItem2_m{};
    // map_unit_param at offset 0x260
    sead::SafeString mEquipItem3_m{};
    // map_unit_param at offset 0x270
    sead::SafeString mEquipItem4_m{};
    // map_unit_param at offset 0x280
    sead::SafeString mRideHorseName_m{};
};

}  // namespace uking::ai
