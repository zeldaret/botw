#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindParentAction : public BindAction {
    SEAD_RTTI_OVERRIDE(BindParentAction, BindAction)
public:
    explicit BindParentAction(const InitArg& arg);
    ~BindParentAction() override;

    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
