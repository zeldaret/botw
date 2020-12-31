#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponSubTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponSubTypeSelect, ksys::act::ai::Ai)
public:
    explicit WeaponSubTypeSelect(const InitArg& arg);
    ~WeaponSubTypeSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai
