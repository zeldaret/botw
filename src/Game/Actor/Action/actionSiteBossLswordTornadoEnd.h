#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordTornadoEnd : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordTornadoEnd, ksys::act::ai::Action)
public:
    explicit SiteBossLswordTornadoEnd(const InitArg& arg);
    ~SiteBossLswordTornadoEnd() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsUseTornadoAttack_s{};
    // dynamic_param at offset 0x28
    ksys::act::BaseProcHandle** mAttackActor_d{};
};

}  // namespace uking::action
