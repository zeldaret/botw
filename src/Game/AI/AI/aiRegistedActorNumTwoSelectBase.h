#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RegistedActorNumTwoSelectBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RegistedActorNumTwoSelectBase, ksys::act::ai::Ai)
public:
    explicit RegistedActorNumTwoSelectBase(const InitArg& arg);
    ~RegistedActorNumTwoSelectBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::ai
