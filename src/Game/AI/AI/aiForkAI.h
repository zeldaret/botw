#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForkAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForkAI, ksys::act::ai::Ai)
public:
    explicit ForkAI(const InitArg& arg);
    ~ForkAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
