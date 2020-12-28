#pragma once

#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageDirectPreTargetBack : public SmallDamageDirectPreTargetBone {
    SEAD_RTTI_OVERRIDE(SmallDamageDirectPreTargetBack, SmallDamageDirectPreTargetBone)
public:
    explicit SmallDamageDirectPreTargetBack(const InitArg& arg);
    ~SmallDamageDirectPreTargetBack() override;

protected:
};

}  // namespace uking::action
