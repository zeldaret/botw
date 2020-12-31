#pragma once

#include "Game/AI/AI/aiBowEquiped.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossBowEquiped : public BowEquiped {
    SEAD_RTTI_OVERRIDE(PriestBossBowEquiped, BowEquiped)
public:
    explicit PriestBossBowEquiped(const InitArg& arg);
    ~PriestBossBowEquiped() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
