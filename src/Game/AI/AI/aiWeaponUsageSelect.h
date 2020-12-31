#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponUsageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponUsageSelect, ksys::act::ai::Ai)
public:
    explicit WeaponUsageSelect(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai
