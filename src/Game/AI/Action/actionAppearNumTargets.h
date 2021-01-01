#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearNumTargets : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearNumTargets, ksys::act::ai::Action)
public:
    explicit AppearNumTargets(const InitArg& arg);
    ~AppearNumTargets() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntTargetCounter_d{};
};

}  // namespace uking::action
