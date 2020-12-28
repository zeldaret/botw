#pragma once

#include "Game/AI/Action/actionEquipedOptionalWeaponAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedQuiver : public EquipedOptionalWeaponAction {
    SEAD_RTTI_OVERRIDE(EquipedQuiver, EquipedOptionalWeaponAction)
public:
    explicit EquipedQuiver(const InitArg& arg);
    ~EquipedQuiver() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
