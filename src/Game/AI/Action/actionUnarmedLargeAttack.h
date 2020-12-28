#pragma once

#include "Game/AI/Action/actionUnarmedAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class UnarmedLargeAttack : public UnarmedAttack {
    SEAD_RTTI_OVERRIDE(UnarmedLargeAttack, UnarmedAttack)
public:
    explicit UnarmedLargeAttack(const InitArg& arg);
    ~UnarmedLargeAttack() override;

protected:
};

}  // namespace uking::action
