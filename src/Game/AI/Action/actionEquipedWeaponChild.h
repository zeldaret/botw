#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedWeaponChild : public BindAction {
    SEAD_RTTI_OVERRIDE(EquipedWeaponChild, BindAction)
public:
    explicit EquipedWeaponChild(const InitArg& arg);
    ~EquipedWeaponChild() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const bool* mIsChangeScale_s{};
};

}  // namespace uking::action
