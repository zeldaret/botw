#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundSetStartProcAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundSetStartProcAction, ksys::act::ai::Action)
public:
    explicit SceneSoundSetStartProcAction(const InitArg& arg);
    ~SceneSoundSetStartProcAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mBgmCtrlType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mSeCtrlType_d{};
};

}  // namespace uking::action
