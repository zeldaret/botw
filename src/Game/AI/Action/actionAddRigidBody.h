#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AddRigidBody : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AddRigidBody, ksys::act::ai::Action)
public:
    explicit AddRigidBody(const InitArg& arg);
    ~AddRigidBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mResetLayer_s{};
};

}  // namespace uking::action
