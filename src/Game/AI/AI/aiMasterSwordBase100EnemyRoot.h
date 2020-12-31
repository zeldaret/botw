#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MasterSwordBase100EnemyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MasterSwordBase100EnemyRoot, ksys::act::ai::Ai)
public:
    explicit MasterSwordBase100EnemyRoot(const InitArg& arg);
    ~MasterSwordBase100EnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mKillAttentionWaitFrame_s{};
};

}  // namespace uking::ai
