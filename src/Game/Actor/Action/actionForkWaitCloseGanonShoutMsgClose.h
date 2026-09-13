#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWaitCloseGanonShoutMsgClose : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkWaitCloseGanonShoutMsgClose, ksys::act::ai::Action)
public:
    explicit ForkWaitCloseGanonShoutMsgClose(const InitArg& arg);
    ~ForkWaitCloseGanonShoutMsgClose() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    bool* mInBeastGanonVoiceSequence_a{};
};

}  // namespace uking::action
