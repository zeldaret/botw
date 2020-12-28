#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoResetBoneCtrl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoResetBoneCtrl, ksys::act::ai::Action)
public:
    explicit DemoResetBoneCtrl(const InitArg& arg);
    ~DemoResetBoneCtrl() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mResetTarget_d{};
};

}  // namespace uking::action
