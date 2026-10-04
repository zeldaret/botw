#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReuseActorDelete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReuseActorDelete, ksys::act::ai::Action)
public:
    explicit ReuseActorDelete(const InitArg& arg);
    ~ReuseActorDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsCheckCreateParent_s{};
    // static_param at offset 0x28
    const bool* mIsCheckBulletAttacker_s{};
    // static_param at offset 0x30
    const bool* mIsCheckBulletHolder_s{};
    // map_unit_param at offset 0x38
    const bool* mIsReuseActor_m{};
};

}  // namespace uking::action
