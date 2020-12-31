#pragma once

#include "Game/AI/AI/aiSeqTimeredTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTimeredPlusRandomTwoAction : public SeqTimeredTwoAction {
    SEAD_RTTI_OVERRIDE(SeqTimeredPlusRandomTwoAction, SeqTimeredTwoAction)
public:
    explicit SeqTimeredPlusRandomTwoAction(const InitArg& arg);
    ~SeqTimeredPlusRandomTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x70
    const int* mFirstActionRandMax_s{};
    // static_param at offset 0x78
    const int* mSecondActionRandMax_s{};
};

}  // namespace uking::ai
