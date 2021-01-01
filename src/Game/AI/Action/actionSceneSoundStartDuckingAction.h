#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundStartDuckingAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundStartDuckingAction, ksys::act::ai::Action)
public:
    explicit SceneSoundStartDuckingAction(const InitArg& arg);
    ~SceneSoundStartDuckingAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mDuckerType_d{};
};

}  // namespace uking::action
