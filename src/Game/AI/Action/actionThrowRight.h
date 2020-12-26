#pragma once

#include "Game/AI/Action/actionThrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowRight : public Throw {
    SEAD_RTTI_OVERRIDE(ThrowRight, Throw)
public:
    explicit ThrowRight(const InitArg& arg);
    ~ThrowRight() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
