#pragma once

#include "Game/AI/Action/actionAnmBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SubAnmBlownOff : public AnmBlownOff {
    SEAD_RTTI_OVERRIDE(SubAnmBlownOff, AnmBlownOff)
public:
    explicit SubAnmBlownOff(const InitArg& arg);
    ~SubAnmBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const int* mSubASSlot_s{};
    // static_param at offset 0xb0
    sead::SafeString mSubAS_s{};
    // static_param at offset 0xc0
    sead::SafeString mLeaveSubAS_s{};
};

}  // namespace uking::action
