#pragma once

#include "Game/AI/Action/actionLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObjectSeachAwareness : public LookAtObject {
    SEAD_RTTI_OVERRIDE(LookAtObjectSeachAwareness, LookAtObject)
public:
    explicit LookAtObjectSeachAwareness(const InitArg& arg);
    ~LookAtObjectSeachAwareness() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xc8
    bool* mIsRetrySearchBaseProc_d{};
};

}  // namespace uking::action
