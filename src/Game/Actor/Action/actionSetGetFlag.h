#pragma once

#include "Game/Actor/Action/actionSetFlag.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetGetFlag : public SetFlag {
    SEAD_RTTI_OVERRIDE(SetGetFlag, SetFlag)
public:
    explicit SetGetFlag(const InitArg& arg);
    ~SetGetFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
