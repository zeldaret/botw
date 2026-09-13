#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EquipedAction, ksys::act::ai::Action)
public:
    explicit EquipedAction(const InitArg& arg);
    ~EquipedAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mNodeName_d{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mRotOffset_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mTransOffset_d{};
};

}  // namespace uking::action
