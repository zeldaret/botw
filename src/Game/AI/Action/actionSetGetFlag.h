#pragma once

#include "Game/AI/Action/actionSetGetFlagBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlag : public SetGetFlagBase {
    SEAD_RTTI_OVERRIDE(SetGetFlag, SetGetFlagBase)
public:
    explicit SetGetFlag(const InitArg& arg);
    ~SetGetFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
