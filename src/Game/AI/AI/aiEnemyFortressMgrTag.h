#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressMgrTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFortressMgrTag, ksys::act::ai::Ai)
public:
    explicit EnemyFortressMgrTag(const InitArg& arg);
    ~EnemyFortressMgrTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCheckInterval_s{};
    // static_param at offset 0x40
    const float* mChangePer_s{};
    // aitree_variable at offset 0x48
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::ai
