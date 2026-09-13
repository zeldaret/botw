#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysOneColTgOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysOneColTgOff, ksys::act::ai::Action)
public:
    explicit ForkAlwaysOneColTgOff(const InitArg& arg);
    ~ForkAlwaysOneColTgOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mRigidBodyName_s{};
};

}  // namespace uking::action
