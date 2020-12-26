#pragma once

#include "Game/AI/Action/actionEquipedOptionalWeaponAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedQuiver : public EquipedOptionalWeaponAction {
    SEAD_RTTI_OVERRIDE(EquipedQuiver, EquipedOptionalWeaponAction)
public:
    explicit EquipedQuiver(const InitArg& arg);
    ~EquipedQuiver() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
