#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundStopDuckingAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundStopDuckingAction, ksys::act::ai::Action)
public:
    explicit SceneSoundStopDuckingAction(const InitArg& arg);
    ~SceneSoundStopDuckingAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mDuckerType_d{};
};

}  // namespace uking::action
