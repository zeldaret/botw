#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DrawnSwordBowSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DrawnSwordBowSelect, ksys::act::ai::Ai)
public:
    explicit DrawnSwordBowSelect(const InitArg& arg);
    ~DrawnSwordBowSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCloseWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mBowWeaponIdx_s{};
};

}  // namespace uking::ai
