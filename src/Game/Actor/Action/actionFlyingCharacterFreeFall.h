#pragma once

#include "Game/Actor/Action/actionFlyingCharacterFreeFallBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreeFall : public FlyingCharacterFreeFallBase {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreeFall, FlyingCharacterFreeFallBase)
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
