#pragma once

#include "Game/AI/Action/actionBackWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackWalkEx : public BackWalkBase {
    SEAD_RTTI_OVERRIDE(BackWalkEx, BackWalkBase)
public:
    explicit BackWalkEx(const InitArg& arg);
    ~BackWalkEx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
