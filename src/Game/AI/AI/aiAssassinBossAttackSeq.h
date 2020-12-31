#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossAttackSeq : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(AssassinBossAttackSeq, SeqTwoAction)
public:
    explicit AssassinBossAttackSeq(const InitArg& arg);
    ~AssassinBossAttackSeq() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
