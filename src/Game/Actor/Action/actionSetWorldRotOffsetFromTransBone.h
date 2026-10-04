#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetWorldRotOffsetFromTransBone : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetWorldRotOffsetFromTransBone, ksys::act::ai::Action)
public:
    explicit SetWorldRotOffsetFromTransBone(const InitArg& arg);
    ~SetWorldRotOffsetFromTransBone() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
