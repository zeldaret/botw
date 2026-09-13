#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaMgr : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaMgr, ksys::act::ai::Action)
public:
    explicit AirOctaMgr(const InitArg& arg);
    ~AirOctaMgr() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLeaveDistance_s{};
    // static_param at offset 0x28
    const float* mLeaveDownY_s{};
    // static_param at offset 0x30
    const float* monGraundEscapeDist_s{};
    // static_param at offset 0x38
    const float* mPlayerLostTime_s{};
    // map_unit_param at offset 0x40
    const float* mMoveDis_m{};
    // map_unit_param at offset 0x48
    const bool* mReactHorn_m{};
};

}  // namespace uking::action
