#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundKillDuckingAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundKillDuckingAction, ksys::act::ai::Action)
public:
    explicit SceneSoundKillDuckingAction(const InitArg& arg);
    ~SceneSoundKillDuckingAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mDuckerType_d{};
};

}  // namespace uking::action
