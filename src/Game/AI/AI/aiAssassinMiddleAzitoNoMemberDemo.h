#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoNoMemberDemo : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoNoMemberDemo, ksys::act::ai::Ai)
public:
    explicit AssassinMiddleAzitoNoMemberDemo(const InitArg& arg);
    ~AssassinMiddleAzitoNoMemberDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDelayTimeMin_s{};
    // static_param at offset 0x40
    const int* mDelayTimeMax_s{};
};

}  // namespace uking::ai
