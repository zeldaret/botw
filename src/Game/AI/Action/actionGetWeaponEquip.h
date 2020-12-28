#pragma once

#include "Game/AI/Action/actionGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetWeaponEquip : public GetItem {
    SEAD_RTTI_OVERRIDE(GetWeaponEquip, GetItem)
public:
    explicit GetWeaponEquip(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
