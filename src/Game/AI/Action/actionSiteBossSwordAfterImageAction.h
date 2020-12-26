#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordAfterImageAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossSwordAfterImageAction, ksys::act::ai::Action)
public:
    explicit SiteBossSwordAfterImageAction(const InitArg& arg);
    ~SiteBossSwordAfterImageAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mCount_m{};
    // aitree_variable at offset 0x28
    void* mSiteBossSwordAfterImageUnit_a{};
};

}  // namespace uking::action
