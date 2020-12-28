#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Search : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Search, ActionWithAS)
public:
    explicit Search(const InitArg& arg);
    ~Search() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mNoChangeTime_s{};
};

}  // namespace uking::action
