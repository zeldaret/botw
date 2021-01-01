#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoForceSetPlayerSavePosAngle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoForceSetPlayerSavePosAngle, ksys::act::ai::Action)
public:
    explicit DemoForceSetPlayerSavePosAngle(const InitArg& arg);
    ~DemoForceSetPlayerSavePosAngle() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mAnchorName_d{};
};

}  // namespace uking::action
