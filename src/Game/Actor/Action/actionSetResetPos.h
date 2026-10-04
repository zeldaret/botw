#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetResetPos : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetResetPos, ksys::act::ai::Action)
public:
    explicit SetResetPos(const InitArg& arg);
    ~SetResetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
