#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Move2HomePosBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Move2HomePosBase, ksys::act::ai::Action)
public:
    explicit Move2HomePosBase(const InitArg& arg);
    ~Move2HomePosBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsReturn_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // dynamic_param at offset 0x30
    float* mDynMoveSpeed_d{};
};

}  // namespace uking::action
