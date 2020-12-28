#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ResetMasterSwordForceState : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ResetMasterSwordForceState, ksys::act::ai::Action)
public:
    explicit ResetMasterSwordForceState(const InitArg& arg);
    ~ResetMasterSwordForceState() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
