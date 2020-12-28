#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Fall : public ActionEx {
    SEAD_RTTI_OVERRIDE(Fall, ActionEx)
public:
    explicit Fall(const InitArg& arg);
    ~Fall() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
