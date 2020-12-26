#pragma once

#include "Game/AI/Action/actionForkASTrgEmitShockWave.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitShockWaveByContact : public ForkASTrgEmitShockWave {
    SEAD_RTTI_OVERRIDE(ForkEmitShockWaveByContact, ForkASTrgEmitShockWave)
public:
    explicit ForkEmitShockWaveByContact(const InitArg& arg);
    ~ForkEmitShockWaveByContact() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    sead::SafeString mRigidBodyName_s{};
};

}  // namespace uking::action
