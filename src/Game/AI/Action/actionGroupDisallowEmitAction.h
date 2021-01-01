#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GroupDisallowEmitAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GroupDisallowEmitAction, ksys::act::ai::Action)
public:
    explicit GroupDisallowEmitAction(const InitArg& arg);
    ~GroupDisallowEmitAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGroupName_d{};
};

}  // namespace uking::action
