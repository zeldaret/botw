#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedRod : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedRod, EquipedAction)
public:
    explicit EquipedRod(const InitArg& arg);
    ~EquipedRod() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const float* mMagicCreateYOffset_s{};
    // static_param at offset 0x48
    const bool* mIsAxisYTop_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mMagicShootVelOffset_s{};
    // static_param at offset 0x58
    const bool* mIsCreateWeaponPosOffset_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mCreatePosOffset_s{};
    // static_param at offset 0x68
    const float* mAxisYAngle_s{};
    // aitree_variable at offset 0x70
    void* mMagicCreateUnit_a{};
};

}  // namespace uking::action
