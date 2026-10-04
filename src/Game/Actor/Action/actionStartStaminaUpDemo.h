#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StartStaminaUpDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StartStaminaUpDemo, ksys::act::ai::Action)
public:
    explicit StartStaminaUpDemo(const InitArg& arg);
    ~StartStaminaUpDemo() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
