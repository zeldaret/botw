#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRoamViewItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoamViewItem, ksys::act::ai::Ai)
public:
    explicit EnemyRoamViewItem(const InitArg& arg);
    ~EnemyRoamViewItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsChanged_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
