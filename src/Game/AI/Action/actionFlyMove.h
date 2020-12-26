#pragma once

#include "Game/AI/Action/actionFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyMove : public FlyMoveBase {
    SEAD_RTTI_OVERRIDE(FlyMove, FlyMoveBase)
public:
    explicit FlyMove(const InitArg& arg);
    ~FlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
