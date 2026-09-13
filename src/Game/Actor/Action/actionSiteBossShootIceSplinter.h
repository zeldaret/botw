#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossShootIceSplinter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossShootIceSplinter, ksys::act::ai::Action)
public:
    explicit SiteBossShootIceSplinter(const InitArg& arg);
    ~SiteBossShootIceSplinter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mThrowIdxOffset_s{};
    // static_param at offset 0x28
    const float* mInitVelocity_s{};
    // static_param at offset 0x30
    sead::SafeString mThrowASName_s{};
    // static_param at offset 0x40
    sead::SafeString mBindNodeName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
