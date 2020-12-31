#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCMove, ksys::act::ai::Ai)
public:
    explicit NPCMove(const InitArg& arg);
    ~NPCMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTerritoryRange_s{};
    // static_param at offset 0x40
    sead::SafeString mDestination_s{};
    // static_param at offset 0x50
    sead::SafeString mMoveEndASName_s{};
};

}  // namespace uking::ai
