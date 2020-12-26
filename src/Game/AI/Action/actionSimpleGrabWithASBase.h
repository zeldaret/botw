#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SimpleGrabWithASBase : public Grab {
    SEAD_RTTI_OVERRIDE(SimpleGrabWithASBase, Grab)
public:
    explicit SimpleGrabWithASBase(const InitArg& arg);
    ~SimpleGrabWithASBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
