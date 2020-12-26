#pragma once

#include "Game/AI/Action/actionForkASTrgDelete.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgDeleteChild : public ForkASTrgDelete {
    SEAD_RTTI_OVERRIDE(ForkASTrgDeleteChild, ForkASTrgDelete)
public:
    explicit ForkASTrgDeleteChild(const InitArg& arg);
    ~ForkASTrgDeleteChild() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
