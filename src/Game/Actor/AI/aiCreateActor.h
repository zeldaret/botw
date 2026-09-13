#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CreateActor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CreateActor, ksys::act::ai::Ai)
public:
    explicit CreateActor(const InitArg& arg);
    ~CreateActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCreatePriorityState_s{};
    // static_param at offset 0x40
    const float* mScale_s{};
    // static_param at offset 0x48
    sead::SafeString mActorName_s{};
};

}  // namespace uking::ai
