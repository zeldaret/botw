#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCWaitAction, ksys::act::ai::Action)
public:
    explicit NPCWaitAction(const InitArg& arg);
    ~NPCWaitAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsIgnoreSameKey_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
