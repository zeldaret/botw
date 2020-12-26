#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateApp : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotateApp, DungeonRotateBase)
public:
    explicit DungeonRotateApp(const InitArg& arg);
    ~DungeonRotateApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const int* mRotDirType_s{};
    // dynamic_param at offset 0xd0
    float* mDynTargetAng_d{};
};

}  // namespace uking::action
