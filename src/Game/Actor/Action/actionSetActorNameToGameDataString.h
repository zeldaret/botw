#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetActorNameToGameDataString : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetActorNameToGameDataString, ksys::act::ai::Action)
public:
    explicit SetActorNameToGameDataString(const InitArg& arg);
    ~SetActorNameToGameDataString() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mGameDataStringName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
