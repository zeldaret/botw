#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AttackHitCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AttackHitCheck, ksys::act::ai::Ai)
public:
    explicit AttackHitCheck(const InitArg& arg);
    ~AttackHitCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAtkType_s{};
};

}  // namespace uking::ai
