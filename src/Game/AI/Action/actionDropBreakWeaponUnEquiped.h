#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DropBreakWeaponUnEquiped : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DropBreakWeaponUnEquiped, ksys::act::ai::Action)
public:
    explicit DropBreakWeaponUnEquiped(const InitArg& arg);
    ~DropBreakWeaponUnEquiped() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mBoundNum_s{};
    // static_param at offset 0x28
    const int* mKillTimer_s{};
};

}  // namespace uking::action
