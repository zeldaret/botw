#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSetComebackPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSetComebackPosition, ksys::act::ai::Action)
public:
    explicit ForkSetComebackPosition(const InitArg& arg);
    ~ForkSetComebackPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
