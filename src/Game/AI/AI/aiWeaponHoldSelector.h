#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponHoldSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponHoldSelector, ksys::act::ai::Ai)
public:
    explicit WeaponHoldSelector(const InitArg& arg);
    ~WeaponHoldSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai
