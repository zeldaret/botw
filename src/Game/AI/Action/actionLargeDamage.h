#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LargeDamage : public ActionEx {
    SEAD_RTTI_OVERRIDE(LargeDamage, ActionEx)
public:
    explicit LargeDamage(const InitArg& arg);
    ~LargeDamage() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mActionTime_s{};
};

}  // namespace uking::action
