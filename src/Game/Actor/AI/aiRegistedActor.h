#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RegistedActor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RegistedActor, ksys::act::ai::Ai)
public:
    explicit RegistedActor(const InitArg& arg);
    ~RegistedActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mRegistedActorUnit_a{};
};

}  // namespace uking::ai
