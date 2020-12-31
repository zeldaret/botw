#pragma once

#include "Game/AI/AI/aiSeqThreeAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqOctarockAttack : public SeqThreeAction {
    SEAD_RTTI_OVERRIDE(SeqOctarockAttack, SeqThreeAction)
public:
    explicit SeqOctarockAttack(const InitArg& arg);
    ~SeqOctarockAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
