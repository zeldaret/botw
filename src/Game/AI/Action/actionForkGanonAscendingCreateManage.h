#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonAscendingCreateManage : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonAscendingCreateManage, ksys::act::ai::Action)
public:
    explicit ForkGanonAscendingCreateManage(const InitArg& arg);
    ~ForkGanonAscendingCreateManage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMaxNum_s{};
    // static_param at offset 0x28
    sead::SafeString mCreateGrudgeName_s{};
};

}  // namespace uking::action
