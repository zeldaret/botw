#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoCookPotCook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoCookPotCook, ksys::act::ai::Action)
public:
    explicit DemoCookPotCook(const InitArg& arg);
    ~DemoCookPotCook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMaterialTargetBone_s{};
    // static_param at offset 0x28
    const int* mFairyTargetBone_s{};
    // dynamic_param at offset 0x30
    bool* mIsSuccess_d{};
    // aitree_variable at offset 0x38
    void* mCurrentCookResultHolder_a{};
};

}  // namespace uking::action
