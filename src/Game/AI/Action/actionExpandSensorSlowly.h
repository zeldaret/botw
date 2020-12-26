#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExpandSensorSlowly : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandSensorSlowly, ksys::act::ai::Action)
public:
    explicit ExpandSensorSlowly(const InitArg& arg);
    ~ExpandSensorSlowly() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtkAttrType_s{};
    // static_param at offset 0x28
    const int* mAtkType_s{};
    // static_param at offset 0x30
    const float* mOffLength_s{};
    // static_param at offset 0x38
    const float* mOnLength_s{};
    // static_param at offset 0x40
    const float* mAtExpandStep_s{};
};

}  // namespace uking::action
