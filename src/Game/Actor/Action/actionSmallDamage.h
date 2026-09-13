#pragma once

#include "Game/Actor/Action/actionSmallDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamage : public SmallDamageBase {
    SEAD_RTTI_OVERRIDE(SmallDamage, SmallDamageBase)
public:
    explicit SmallDamage(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
