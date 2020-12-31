#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyPermitAttackSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyPermitAttackSelect, ksys::act::ai::Ai)
public:
    explicit EnemyPermitAttackSelect(const InitArg& arg);
    ~EnemyPermitAttackSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsIgnoreEnemyMgr_s{};
};

}  // namespace uking::ai
