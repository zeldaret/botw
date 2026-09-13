#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TreasureBoxBurnedOut : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TreasureBoxBurnedOut, ksys::act::ai::Action)
public:
    explicit TreasureBoxBurnedOut(const InitArg& arg);
    ~TreasureBoxBurnedOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x20];
    // aitree_variable at offset 0x40
    bool* mIsOpenTreasureBox_a{};
    // aitree_variable at offset 0x48
    sead::SafeString* mDropActorName_a{};
    // aitree_variable at offset 0x50
    void* mSharpWeaponAddParam_a{};
};

}  // namespace uking::action
