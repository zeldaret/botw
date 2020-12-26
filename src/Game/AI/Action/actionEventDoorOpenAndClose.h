#pragma once

#include "Game/AI/Action/actionDoorOpenAndClose.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventDoorOpenAndClose : public DoorOpenAndClose {
    SEAD_RTTI_OVERRIDE(EventDoorOpenAndClose, DoorOpenAndClose)
public:
    explicit EventDoorOpenAndClose(const InitArg& arg);
    ~EventDoorOpenAndClose() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x38
    bool* mDynIsOpenToInside_d{};
    // dynamic_param at offset 0x40
    bool* mDynIsOpen_d{};
    // aitree_variable at offset 0x48
    bool* mIsOpenDoor_a{};
    // aitree_variable at offset 0x50
    bool* mIsOpenToInside_a{};
};

}  // namespace uking::action
