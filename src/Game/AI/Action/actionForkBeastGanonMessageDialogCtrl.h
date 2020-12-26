#pragma once

#include "Game/AI/Action/actionSimpleMessageDialogCtrl.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkBeastGanonMessageDialogCtrl : public SimpleMessageDialogCtrl {
    SEAD_RTTI_OVERRIDE(ForkBeastGanonMessageDialogCtrl, SimpleMessageDialogCtrl)
public:
    explicit ForkBeastGanonMessageDialogCtrl(const InitArg& arg);
    ~ForkBeastGanonMessageDialogCtrl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x30
    int* mGanonBeastVoiceSequenceCount_a{};
    // aitree_variable at offset 0x38
    bool* mInBeastGanonVoiceSequence_a{};
};

}  // namespace uking::action
