#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GraveAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GraveAttack, ksys::act::ai::Action)
public:
    explicit GraveAttack(const InitArg& arg);
    ~GraveAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mAttackPower_m{};
    // static_param at offset 0x28
    const int* mTime_s{};
    // static_param at offset 0x30
    const int* mKeepTime_s{};
};

}  // namespace uking::action
