#pragma once

#include "Game/AI/AI/aiSeqGroundHit.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqGroundHitAssassinBoss : public SeqGroundHit {
    SEAD_RTTI_OVERRIDE(SeqGroundHitAssassinBoss, SeqGroundHit)
public:
    explicit SeqGroundHitAssassinBoss(const InitArg& arg);
    ~SeqGroundHitAssassinBoss() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
