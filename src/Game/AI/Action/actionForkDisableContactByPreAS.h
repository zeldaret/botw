#pragma once

#include "Game/AI/Action/actionForkDisableContact.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDisableContactByPreAS : public ForkDisableContact {
    SEAD_RTTI_OVERRIDE(ForkDisableContactByPreAS, ForkDisableContact)
public:
    explicit ForkDisableContactByPreAS(const InitArg& arg);
    ~ForkDisableContactByPreAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const int* mDisableTime_s{};
};

}  // namespace uking::action
