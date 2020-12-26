#pragma once

#include "Game/AI/Action/actionAreaFireObserveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserve : public AreaFireObserveBase {
    SEAD_RTTI_OVERRIDE(AreaFireObserve, AreaFireObserveBase)
public:
    explicit AreaFireObserve(const InitArg& arg);
    ~AreaFireObserve() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
