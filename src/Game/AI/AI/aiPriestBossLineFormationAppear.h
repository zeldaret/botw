#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossLineFormationAppear : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(PriestBossLineFormationAppear, SeqTwoAction)
public:
    explicit PriestBossLineFormationAppear(const InitArg& arg);
    ~PriestBossLineFormationAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
