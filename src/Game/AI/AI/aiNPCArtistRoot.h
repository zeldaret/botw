#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCArtistRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCArtistRoot, NPCRoot)
public:
    explicit NPCArtistRoot(const InitArg& arg);
    ~NPCArtistRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x238
    sead::SafeString mActorName_m{};
};

}  // namespace uking::ai
