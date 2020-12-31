#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCRoot, ksys::act::ai::Ai)
public:
    explicit NPCRoot(const InitArg& arg);
    ~NPCRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mReleaseInterest2Time_s{};
    // static_param at offset 0x40
    const float* mPlayerHitVelocity_s{};
    // static_param at offset 0x48
    sead::SafeString mStaggerUpperASName_s{};
    // static_param at offset 0x58
    sead::SafeString mStaggerUpperRunASName_s{};
};

}  // namespace uking::ai
