#pragma once

#include "Game/AI/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitChmField : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkEmitChmField, ForkEmitExpandField)
public:
    explicit ForkEmitChmField(const InitArg& arg);
    ~ForkEmitChmField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mEmitIntervalTime_s{};
};

}  // namespace uking::action
