#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemApplyEnvSetAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SystemApplyEnvSetAction, ksys::act::ai::Action)
public:
    explicit SystemApplyEnvSetAction(const InitArg& arg);
    ~SystemApplyEnvSetAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mEnvSetName_d{};
};

}  // namespace uking::action
