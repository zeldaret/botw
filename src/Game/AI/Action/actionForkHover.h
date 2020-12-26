#pragma once

#include "Game/AI/Action/actionHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHover : public HoverBase {
    SEAD_RTTI_OVERRIDE(ForkHover, HoverBase)
public:
    explicit ForkHover(const InitArg& arg);
    ~ForkHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
