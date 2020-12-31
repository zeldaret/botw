#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTargetGearSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyTargetGearSelect, ksys::act::ai::Ai)
public:
    explicit EnemyTargetGearSelect(const InitArg& arg);
    ~EnemyTargetGearSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mGearThreashold_s{};
    // static_param at offset 0x40
    const bool* mIsSelectEveryFrame_s{};
};

}  // namespace uking::ai
