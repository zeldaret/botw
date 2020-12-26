#pragma once

#include "Game/AI/Action/actionUnarmedAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class UnarmedLargeAttack : public UnarmedAttack {
    SEAD_RTTI_OVERRIDE(UnarmedLargeAttack, UnarmedAttack)
public:
    explicit UnarmedLargeAttack(const InitArg& arg);
    ~UnarmedLargeAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
