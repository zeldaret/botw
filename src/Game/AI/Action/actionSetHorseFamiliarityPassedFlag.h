#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetHorseFamiliarityPassedFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetHorseFamiliarityPassedFlag, ksys::act::ai::Action)
public:
    explicit SetHorseFamiliarityPassedFlag(const InitArg& arg);
    ~SetHorseFamiliarityPassedFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
