#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ItemConductorDemoBind : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ItemConductorDemoBind, ksys::act::ai::Action)
public:
    explicit ItemConductorDemoBind(const InitArg& arg);
    ~ItemConductorDemoBind() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mRotOffsetX_d{};
    // dynamic_param at offset 0x28
    float* mRotOffsetY_d{};
    // dynamic_param at offset 0x30
    float* mRotOffsetZ_d{};
    // dynamic_param at offset 0x38
    float* mTransOffsetX_d{};
    // dynamic_param at offset 0x40
    float* mTransOffsetY_d{};
    // dynamic_param at offset 0x48
    float* mTransOffsetZ_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mNodeName_d{};
};

}  // namespace uking::action
