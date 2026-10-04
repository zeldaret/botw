#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireWoodBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FireWoodBase, ksys::act::ai::Action)
public:
    explicit FireWoodBase(const InitArg& arg);
    ~FireWoodBase() override;

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
