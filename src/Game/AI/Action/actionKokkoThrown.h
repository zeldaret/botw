#pragma once

#include "Game/AI/Action/actionThrown.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KokkoThrown : public Thrown {
    SEAD_RTTI_OVERRIDE(KokkoThrown, Thrown)
public:
    explicit KokkoThrown(const InitArg& arg);
    ~KokkoThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const float* mGravityScale_s{};
    // aitree_variable at offset 0xb8
    bool* mIsChangeableStateFreeFall_a{};
};

}  // namespace uking::action
