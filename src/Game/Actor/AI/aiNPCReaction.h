#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCReaction, ksys::act::ai::Ai)
public:
    explicit NPCReaction(const InitArg& arg);
    ~NPCReaction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    int* mReactionId_d{};
    // dynamic_param at offset 0x40
    bool* mIsReceiveInterest2_d{};
    // dynamic_param at offset 0x48
    sead::SafeString* mMessageId_d{};
    // dynamic_param at offset 0x58
    sead::SafeString* mGazeASName_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mStaggerDir_d{};
};

}  // namespace uking::ai
