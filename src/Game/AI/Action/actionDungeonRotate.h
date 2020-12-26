#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotate : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotate, DungeonRotateBase)
public:
    explicit DungeonRotate(const InitArg& arg);
    ~DungeonRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0xc8
    const int* mDgnRotDir_m{};
};

}  // namespace uking::action
