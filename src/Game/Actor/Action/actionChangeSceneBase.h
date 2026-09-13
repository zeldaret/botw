#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeSceneBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeSceneBase, ksys::act::ai::Action)
public:
    explicit ChangeSceneBase(const InitArg& arg);
    ~ChangeSceneBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mStartType_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mEvflName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mEntryPointName_d{};
};

}  // namespace uking::action
