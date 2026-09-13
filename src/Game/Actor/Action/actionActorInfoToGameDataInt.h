#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActorInfoToGameDataInt : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ActorInfoToGameDataInt, ksys::act::ai::Action)
public:
    explicit ActorInfoToGameDataInt(const InitArg& arg);
    ~ActorInfoToGameDataInt() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mGameDataIntToName_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mParameterName_d{};
};

}  // namespace uking::action
