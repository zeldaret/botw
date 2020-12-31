#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressChat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFortressChat, ksys::act::ai::Ai)
public:
    explicit EnemyFortressChat(const InitArg& arg);
    ~EnemyFortressChat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mNextPer_s{};
    // aitree_variable at offset 0x40
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::ai
