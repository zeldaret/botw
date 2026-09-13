#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeActiveEnemy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeActiveEnemy, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeActiveEnemy(const InitArg& arg);
    ~EnemyNoticeActiveEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
