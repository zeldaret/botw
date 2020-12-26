#pragma once

#include "Game/AI/Action/actionBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Balloon : public BalloonBase {
    SEAD_RTTI_OVERRIDE(Balloon, BalloonBase)
public:
    explicit Balloon(const InitArg& arg);
    ~Balloon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf0
    const float* mLength_s{};
    // static_param at offset 0xf8
    sead::SafeString mRopeActorName_s{};
    // map_unit_param at offset 0x108
    const sead::Vector3f* mRopeHungActOffset_m{};
};

}  // namespace uking::action
