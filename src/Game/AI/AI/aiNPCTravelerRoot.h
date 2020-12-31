#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCTravelerRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCTravelerRoot, NPCRoot)
public:
    explicit NPCTravelerRoot(const InitArg& arg);
    ~NPCTravelerRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x238
    const bool* mIsRiderChangableAction_s{};
};

}  // namespace uking::ai
