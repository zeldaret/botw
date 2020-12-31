#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnvSeEmitPointRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnvSeEmitPointRootAI, ksys::act::ai::Ai)
public:
    explicit EnvSeEmitPointRootAI(const InitArg& arg);
    ~EnvSeEmitPointRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mInvalidatePlayDistance_s{};
    // static_param at offset 0x40
    const float* mPlayDistance_s{};
};

}  // namespace uking::ai
