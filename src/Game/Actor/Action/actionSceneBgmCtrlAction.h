#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneBgmCtrlAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneBgmCtrlAction, ksys::act::ai::Action)
public:
    explicit SceneBgmCtrlAction(const InitArg& arg);
    ~SceneBgmCtrlAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mCtrlType_d{};
};

}  // namespace uking::action
