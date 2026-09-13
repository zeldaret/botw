#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySittingTogether : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemySittingTogether, ksys::act::ai::Ai)
public:
    explicit EnemySittingTogether(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsNextActionReserved_a{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
