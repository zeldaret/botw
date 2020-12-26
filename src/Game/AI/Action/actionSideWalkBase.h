#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideWalkBase : public MoveBase {
    SEAD_RTTI_OVERRIDE(SideWalkBase, MoveBase)
public:
    explicit SideWalkBase(const InitArg& arg);
    ~SideWalkBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    const bool* mLeftMove_s{};
};

}  // namespace uking::action
