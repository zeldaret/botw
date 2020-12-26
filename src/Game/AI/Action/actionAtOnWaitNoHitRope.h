#pragma once

#include "Game/AI/Action/actionAtOnWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AtOnWaitNoHitRope : public AtOnWait {
    SEAD_RTTI_OVERRIDE(AtOnWaitNoHitRope, AtOnWait)
public:
    explicit AtOnWaitNoHitRope(const InitArg& arg);
    ~AtOnWaitNoHitRope() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const int* mAtkAttrType_s{};
};

}  // namespace uking::action
