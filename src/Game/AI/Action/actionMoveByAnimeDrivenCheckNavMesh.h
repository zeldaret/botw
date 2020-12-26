#pragma once

#include "Game/AI/Action/actionMoveByAnimeDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveByAnimeDrivenCheckNavMesh : public MoveByAnimeDriven {
    SEAD_RTTI_OVERRIDE(MoveByAnimeDrivenCheckNavMesh, MoveByAnimeDriven)
public:
    explicit MoveByAnimeDrivenCheckNavMesh(const InitArg& arg);
    ~MoveByAnimeDrivenCheckNavMesh() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
