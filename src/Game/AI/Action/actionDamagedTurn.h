#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DamagedTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DamagedTurn, ksys::act::ai::Action)
public:
    explicit DamagedTurn(const InitArg& arg);
    ~DamagedTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mRotRatio_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
