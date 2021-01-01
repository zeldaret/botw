#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceSetPlayerRestartPosAngle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceSetPlayerRestartPosAngle, ksys::act::ai::Action)
public:
    explicit ForceSetPlayerRestartPosAngle(const InitArg& arg);
    ~ForceSetPlayerRestartPosAngle() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mAnchorName_d{};
};

}  // namespace uking::action
