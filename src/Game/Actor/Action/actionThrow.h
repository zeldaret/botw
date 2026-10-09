#pragma once

#include "Game/Actor/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Throw : public StopBase {
    SEAD_RTTI_OVERRIDE(Throw, StopBase)
public:
    explicit Throw(const InitArg& arg);
    ~Throw() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
