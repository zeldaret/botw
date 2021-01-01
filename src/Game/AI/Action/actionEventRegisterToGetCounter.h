#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventRegisterToGetCounter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventRegisterToGetCounter, ksys::act::ai::Action)
public:
    explicit EventRegisterToGetCounter(const InitArg& arg);
    ~EventRegisterToGetCounter() override;

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
