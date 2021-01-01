#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventRegisterToDeathConter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventRegisterToDeathConter, ksys::act::ai::Action)
public:
    explicit EventRegisterToDeathConter(const InitArg& arg);
    ~EventRegisterToDeathConter() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsInitializeData_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mGameDataName_d{};
};

}  // namespace uking::action
