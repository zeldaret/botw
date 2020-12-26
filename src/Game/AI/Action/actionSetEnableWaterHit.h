#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetEnableWaterHit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetEnableWaterHit, ksys::act::ai::Action)
public:
    explicit SetEnableWaterHit(const InitArg& arg);
    ~SetEnableWaterHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mWaterHit_s{};
};

}  // namespace uking::action
