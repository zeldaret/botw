#pragma once

#include "Game/Actor/AI/aiAddViewTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddViewTargetPos : public AddViewTarget {
    SEAD_RTTI_OVERRIDE(AddViewTargetPos, AddViewTarget)
public:
    explicit AddViewTargetPos(const InitArg& arg);
    ~AddViewTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
