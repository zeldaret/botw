#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAutoSaveAtGameClear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAutoSaveAtGameClear, ksys::act::ai::Action)
public:
    explicit EventAutoSaveAtGameClear(const InitArg& arg);
    ~EventAutoSaveAtGameClear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mRestartYDegree_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameClearFlag_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mRestartPoint_d{};
};

}  // namespace uking::action
