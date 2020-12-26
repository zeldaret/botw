#pragma once

#include "Game/AI/Action/actionKokkoMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KokkoMoveWithJump : public KokkoMove {
    SEAD_RTTI_OVERRIDE(KokkoMoveWithJump, KokkoMove)
public:
    explicit KokkoMoveWithJump(const InitArg& arg);
    ~KokkoMoveWithJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mJumpSpeed_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mJumpDir_s{};
    // dynamic_param at offset 0xa8
    bool* mIsJump_d{};
};

}  // namespace uking::action
