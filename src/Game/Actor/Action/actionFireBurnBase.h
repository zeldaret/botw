#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireBurnBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FireBurnBase, ksys::act::ai::Action)
public:
    explicit FireBurnBase(const InitArg& arg);
    ~FireBurnBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mChemicalRigidOn_s{};
    // map_unit_param at offset 0x28
    const bool* mInitBurnState_m{};
};

}  // namespace uking::action
