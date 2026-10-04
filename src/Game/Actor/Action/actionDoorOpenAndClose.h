#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DoorOpenAndClose : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DoorOpenAndClose, ksys::act::ai::Action)
public:
    explicit DoorOpenAndClose(const InitArg& arg);
    ~DoorOpenAndClose() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mDynASKey_d{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mDynOwner_d{};
};

}  // namespace uking::action
