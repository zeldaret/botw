#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCGerudoQueenRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCGerudoQueenRoot, NPCRoot)
public:
    explicit NPCGerudoQueenRoot(const InitArg& arg);
    ~NPCGerudoQueenRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x238
    const bool* mIsOnHelmet_m{};
};

}  // namespace uking::ai
