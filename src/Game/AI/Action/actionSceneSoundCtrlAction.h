#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundCtrlAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundCtrlAction, ksys::act::ai::Action)
public:
    explicit SceneSoundCtrlAction(const InitArg& arg);
    ~SceneSoundCtrlAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mBgmCtrlType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mSeCtrlType_d{};
};

}  // namespace uking::action
