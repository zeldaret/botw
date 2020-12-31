#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallAttackLevelSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallAttackLevelSelect, ksys::act::ai::Ai)
public:
    explicit WillBallAttackLevelSelect(const InitArg& arg);
    ~WillBallAttackLevelSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    int* mLevel_d{};
};

}  // namespace uking::ai
