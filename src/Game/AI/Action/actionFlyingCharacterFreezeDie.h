#pragma once

#include "Game/AI/Action/actionFlyingCharacterFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreezeDie : public FlyingCharacterFreeze {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreezeDie, FlyingCharacterFreeze)
public:
    explicit FlyingCharacterFreezeDie(const InitArg& arg);
    ~FlyingCharacterFreezeDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
