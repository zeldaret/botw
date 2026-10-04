#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeSound, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeSound(const InitArg& arg);
    ~EnemyNoticeSound() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
