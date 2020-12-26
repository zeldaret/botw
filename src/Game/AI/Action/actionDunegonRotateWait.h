#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DunegonRotateWait : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DunegonRotateWait, DungeonRotateBase)
public:
    explicit DunegonRotateWait(const InitArg& arg);
    ~DunegonRotateWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
