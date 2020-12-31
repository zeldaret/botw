#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelRepeatAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRepeatAttack, ksys::act::ai::Ai)
public:
    explicit LynelRepeatAttack(const InitArg& arg);
    ~LynelRepeatAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackNum_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
};

}  // namespace uking::ai
