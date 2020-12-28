#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForceMasterSwordFakeMode : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForceMasterSwordFakeMode, ksys::act::ai::Action)
public:
    explicit ForceMasterSwordFakeMode(const InitArg& arg);
    ~ForceMasterSwordFakeMode() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
