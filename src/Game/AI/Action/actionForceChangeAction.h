#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceChangeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceChangeAction, ksys::act::ai::Action)
public:
    explicit ForceChangeAction(const InitArg& arg);
    ~ForceChangeAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mTree_s{};
};

}  // namespace uking::action
