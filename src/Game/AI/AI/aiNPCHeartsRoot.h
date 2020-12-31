#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCHeartsRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCHeartsRoot, NPCRoot)
public:
    explicit NPCHeartsRoot(const InitArg& arg);
    ~NPCHeartsRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
