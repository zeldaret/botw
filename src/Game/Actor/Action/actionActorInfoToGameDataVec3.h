#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActorInfoToGameDataVec3 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ActorInfoToGameDataVec3, ksys::act::ai::Action)
public:
    explicit ActorInfoToGameDataVec3(const InitArg& arg);
    ~ActorInfoToGameDataVec3() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mGameDataVec3fToName_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mParameterName_d{};
};

}  // namespace uking::action
