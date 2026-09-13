#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleKokkoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleKokkoRoot, ksys::act::ai::Ai)
public:
    explicit SimpleKokkoRoot(const InitArg& arg);
    ~SimpleKokkoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAliveTime_s{};
    // aitree_variable at offset 0x40
    void* mAttackTargetActorLink_a{};
};

}  // namespace uking::ai
