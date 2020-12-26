#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossSideMove : public MoveBase {
    SEAD_RTTI_OVERRIDE(PriestBossSideMove, MoveBase)
public:
    explicit PriestBossSideMove(const InitArg& arg);
    ~PriestBossSideMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    const int* mRotDir_s{};
    // static_param at offset 0xe8
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
