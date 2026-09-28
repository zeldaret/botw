#pragma once

#include "Game/Actor/Action/actionBackWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NormalBackWalk : public BackWalkBase {
    SEAD_RTTI_OVERRIDE(NormalBackWalk, BackWalkBase)
public:
    explicit NormalBackWalk(const InitArg& arg);
    ~NormalBackWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
