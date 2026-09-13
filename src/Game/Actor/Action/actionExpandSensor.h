#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExpandSensor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandSensor, ksys::act::ai::Action)
public:
    explicit ExpandSensor(const InitArg& arg);
    ~ExpandSensor() override;

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
};

}  // namespace uking::action
