#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTimeredTwoAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTimeredTwoAction, ksys::act::ai::Ai)
public:
    explicit SeqTimeredTwoAction(const InitArg& arg);
    ~SeqTimeredTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFirstActionTime_s{};
    // static_param at offset 0x40
    const int* mSecondActionTime_s{};
    // static_param at offset 0x48
    const int* mAllActionTime_s{};
};

}  // namespace uking::ai
