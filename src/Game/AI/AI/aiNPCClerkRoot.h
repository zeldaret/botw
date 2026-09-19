#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCClerkRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCClerkRoot, NPCRoot)
public:
    bool hasPreDeleteCb() override { return true; }
    explicit NPCClerkRoot(const InitArg& arg);
    ~NPCClerkRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
