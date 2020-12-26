#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateCont : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotateCont, DungeonRotateBase)
public:
    explicit DungeonRotateCont(const InitArg& arg);
    ~DungeonRotateCont() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0xc8
    const int* mDgnRotDir_m{};
    // map_unit_param at offset 0xd0
    const float* mTiltAngle_m{};
    // aitree_variable at offset 0xd8
    bool* mIsContinueRotateOrMove_a{};
};

}  // namespace uking::action
