#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TreasureBox : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TreasureBox, ksys::act::ai::Ai)
public:
    explicit TreasureBox(const InitArg& arg);
    ~TreasureBox() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mSharpWeaponJudgeType_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mDropActor_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mDropTable_m{};
    // aitree_variable at offset 0x60
    bool* mIsOpenTreasureBox_a{};
    // aitree_variable at offset 0x68
    bool* mIsSetupDropActor_a{};
    // aitree_variable at offset 0x70
    sead::SafeString* mDropActorName_a{};
    // aitree_variable at offset 0x78
    void* mSharpWeaponAddParam_a{};
};

}  // namespace uking::ai
