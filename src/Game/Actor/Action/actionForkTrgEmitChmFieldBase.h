#pragma once

#include "Game/Actor/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTrgEmitChmFieldBase : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkTrgEmitChmFieldBase, ForkEmitExpandField)
public:
    explicit ForkTrgEmitChmFieldBase(const InitArg& arg);
    ~ForkTrgEmitChmFieldBase() override;

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
