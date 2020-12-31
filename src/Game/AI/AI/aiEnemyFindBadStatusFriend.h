#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFindBadStatusFriend : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFindBadStatusFriend, ksys::act::ai::Ai)
public:
    explicit EnemyFindBadStatusFriend(const InitArg& arg);
    ~EnemyFindBadStatusFriend() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
