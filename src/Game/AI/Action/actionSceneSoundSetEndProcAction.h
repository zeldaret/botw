#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SceneSoundSetEndProcAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SceneSoundSetEndProcAction, ksys::act::ai::Action)
public:
    explicit SceneSoundSetEndProcAction(const InitArg& arg);
    ~SceneSoundSetEndProcAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mCtrlType_d{};
};

}  // namespace uking::action
