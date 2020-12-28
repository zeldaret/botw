#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerReleaseMasterSowrd : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerReleaseMasterSowrd, ksys::act::ai::Action)
public:
    explicit PlayerReleaseMasterSowrd(const InitArg& arg);
    ~PlayerReleaseMasterSowrd() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
