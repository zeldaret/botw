#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossShieldBash : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossShieldBash, ksys::act::ai::Ai)
public:
    explicit LastBossShieldBash(const InitArg& arg);
    ~LastBossShieldBash() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsAttackPatternFixed_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
