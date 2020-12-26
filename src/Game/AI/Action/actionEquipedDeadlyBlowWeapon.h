#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedDeadlyBlowWeapon : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedDeadlyBlowWeapon, EquipedAction)
public:
    explicit EquipedDeadlyBlowWeapon(const InitArg& arg);
    ~EquipedDeadlyBlowWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
