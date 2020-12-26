#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObjDlcGondolaCreateTag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DgnObjDlcGondolaCreateTag, ksys::act::ai::Action)
public:
    explicit DgnObjDlcGondolaCreateTag(const InitArg& arg);
    ~DgnObjDlcGondolaCreateTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mActorName_s{};
    // map_unit_param at offset 0x30
    const float* mIntervalTime_m{};
    // map_unit_param at offset 0x38
    const float* mRailMoveSpeed_m{};
};

}  // namespace uking::action
