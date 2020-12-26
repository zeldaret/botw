#pragma once

#include "Game/AI/Action/actionHorseSaddleDefaultAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseSaddleBindAction : public HorseSaddleDefaultAction {
    SEAD_RTTI_OVERRIDE(HorseSaddleBindAction, HorseSaddleDefaultAction)
public:
    explicit HorseSaddleBindAction(const InitArg& arg);
    ~HorseSaddleBindAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x1a40
    bool* mIsLeftBind_d{};
    // dynamic_param at offset 0x1a48
    bool* mIsRightBind_d{};
    // dynamic_param at offset 0x1a50
    bool* mIsZelda_d{};
    // dynamic_param at offset 0x1a58
    ksys::act::BaseProcLink* mRider_d{};
    // dynamic_param at offset 0x1a60
    ksys::act::BaseProcLink* mHorse_d{};
};

}  // namespace uking::action
