#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventBind : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventBind, ksys::act::ai::Action)
public:
    explicit EventBind(const InitArg& arg);
    ~EventBind() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mEventBindUnit_a{};
    // dynamic_param at offset 0x28
    float* mRotOffsetX_d{};
    // dynamic_param at offset 0x30
    float* mRotOffsetY_d{};
    // dynamic_param at offset 0x38
    float* mRotOffsetZ_d{};
    // dynamic_param at offset 0x40
    float* mTransOffsetX_d{};
    // dynamic_param at offset 0x48
    float* mTransOffsetY_d{};
    // dynamic_param at offset 0x50
    float* mTransOffsetZ_d{};
    // dynamic_param at offset 0x58
    bool* mIsContinueBind_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x80
    sead::SafeString mNodeName_d{};
};

}  // namespace uking::action
