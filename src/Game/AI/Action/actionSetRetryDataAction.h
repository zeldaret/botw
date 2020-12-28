#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetRetryDataAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetRetryDataAction, ksys::act::ai::Action)
public:
    explicit SetRetryDataAction(const InitArg& arg);
    ~SetRetryDataAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
