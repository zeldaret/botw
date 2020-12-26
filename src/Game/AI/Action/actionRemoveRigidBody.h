#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemoveRigidBody : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemoveRigidBody, ksys::act::ai::Action)
public:
    explicit RemoveRigidBody(const InitArg& arg);
    ~RemoveRigidBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mChangeLayer_s{};
};

}  // namespace uking::action
