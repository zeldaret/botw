#pragma once

#include "Game/AI/Action/actionLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyMove : public LevelFlyMoveBase {
    SEAD_RTTI_OVERRIDE(LevelFlyMove, LevelFlyMoveBase)
public:
    explicit LevelFlyMove(const InitArg& arg);
    ~LevelFlyMove() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
