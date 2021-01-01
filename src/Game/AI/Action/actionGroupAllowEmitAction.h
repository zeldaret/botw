#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GroupAllowEmitAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GroupAllowEmitAction, ksys::act::ai::Action)
public:
    explicit GroupAllowEmitAction(const InitArg& arg);
    ~GroupAllowEmitAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGroupName_d{};
};

}  // namespace uking::action
