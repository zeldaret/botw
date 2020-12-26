#pragma once

#include "Game/AI/Action/actionForkEmitChmField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitChmFieldByContact : public ForkEmitChmField {
    SEAD_RTTI_OVERRIDE(ForkEmitChmFieldByContact, ForkEmitChmField)
public:
    explicit ForkEmitChmFieldByContact(const InitArg& arg);
    ~ForkEmitChmFieldByContact() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    sead::SafeString mRigidBodyName_s{};
};

}  // namespace uking::action
