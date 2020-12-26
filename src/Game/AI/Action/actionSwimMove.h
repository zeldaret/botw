#pragma once

#include "Game/AI/Action/actionSwimMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimMove : public SwimMoveBase {
    SEAD_RTTI_OVERRIDE(SwimMove, SwimMoveBase)
public:
    explicit SwimMove(const InitArg& arg);
    ~SwimMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
