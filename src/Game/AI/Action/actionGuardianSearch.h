#pragma once

#include "Game/AI/Action/actionGuardianMoveTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianSearch : public GuardianMoveTo {
    SEAD_RTTI_OVERRIDE(GuardianSearch, GuardianMoveTo)
public:
    explicit GuardianSearch(const InitArg& arg);
    ~GuardianSearch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWaitFrame_s{};
    // static_param at offset 0x38
    const bool* mLost_s{};
};

}  // namespace uking::action
