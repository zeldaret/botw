#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkVacuumShootToTarget : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkVacuumShootToTarget, ksys::act::ai::Action)
public:
    explicit ForkVacuumShootToTarget(const InitArg& arg);
    ~ForkVacuumShootToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0xa8];
    // static_param at offset 0xc8
    const bool* mIsReuseBullet_s{};
};

}  // namespace uking::action
