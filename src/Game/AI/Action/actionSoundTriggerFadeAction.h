#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SoundTriggerFadeAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SoundTriggerFadeAction, ksys::act::ai::Action)
public:
    explicit SoundTriggerFadeAction(const InitArg& arg);
    ~SoundTriggerFadeAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
};

}  // namespace uking::action
