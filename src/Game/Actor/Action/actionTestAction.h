#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TestAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TestAction, ksys::act::ai::Action)
public:
    explicit TestAction(const InitArg& arg);
    ~TestAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mFlag_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mName_d{};
};

}  // namespace uking::action
