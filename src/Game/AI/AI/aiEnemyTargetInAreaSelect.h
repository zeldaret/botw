#pragma once

#include "Game/AI/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTargetInAreaSelect : public TargetInAreaSelect {
    SEAD_RTTI_OVERRIDE(EnemyTargetInAreaSelect, TargetInAreaSelect)
public:
    explicit EnemyTargetInAreaSelect(const InitArg& arg);
    ~EnemyTargetInAreaSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mLengthXZ_s{};
    // static_param at offset 0x48
    const float* mLengthMaxY_s{};
    // static_param at offset 0x50
    const float* mLengthMinY_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mCentOffset_s{};
};

}  // namespace uking::ai
