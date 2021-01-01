#pragma once

#include "Game/AI/Action/actionSetGetFlagBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlagByActorName : public SetGetFlagBase {
    SEAD_RTTI_OVERRIDE(SetGetFlagByActorName, SetGetFlagBase)
public:
    explicit SetGetFlagByActorName(const InitArg& arg);
    ~SetGetFlagByActorName() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
