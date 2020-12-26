#pragma once

#include "Game/AI/Action/actionWizzrobeVisibleWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ViewLevelFlyMove : public WizzrobeVisibleWalk {
    SEAD_RTTI_OVERRIDE(ViewLevelFlyMove, WizzrobeVisibleWalk)
public:
    explicit ViewLevelFlyMove(const InitArg& arg);
    ~ViewLevelFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x178
    sead::Vector3f* mAttPos_d{};
};

}  // namespace uking::action
