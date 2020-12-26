#pragma once

#include "Game/AI/Action/actionFlyingCharacterReaction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreeFall : public FlyingCharacterReaction {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreeFall, FlyingCharacterReaction)
public:
    explicit FlyingCharacterFreeFall(const InitArg& arg);
    ~FlyingCharacterFreeFall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
